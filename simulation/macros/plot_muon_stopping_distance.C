// Draw the primary mu- stopping-depth distribution written by muonB10.
//
// Run from the directory that holds the output file (e.g. simulation/):
//   root -l macros/plot_muon_stopping_distance.C
//   root -l 'macros/plot_muon_stopping_distance.C("path/to/muon_stopping.root")'
//   root -l 'macros/plot_muon_stopping_distance.C("muon_stopping.root", true)'  // log y

#include <TCanvas.h>
#include <TError.h>
#include <TFile.h>
#include <TH1.h>
#include <TLatex.h>
#include <TLine.h>
#include <TString.h>
#include <TStyle.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <memory>

namespace {
// Interpolated x where the histogram crosses `level`, walking from bin `from`
// in direction `dir` (-1 left, +1 right). Returns NaN if it never crosses.
double crossing(const TH1 *h, int from, int dir, double level) {
  for (int i = from; i >= 1 && i <= h->GetNbinsX(); i += dir) {
    const double y = h->GetBinContent(i);
    if (y < level) {
      const int j = i - dir; // last bin still above the level
      const double x0 = h->GetBinCenter(i), y0 = y;
      const double x1 = h->GetBinCenter(j), y1 = h->GetBinContent(j);
      return x0 + (level - y0) * (x1 - x0) / (y1 - y0);
    }
  }
  return std::nan("");
}
} // namespace

void plot_muon_stopping_distance(const char *path = "muon_stopping.root",
                                 bool logy = false) {
  std::unique_ptr<TFile> file(TFile::Open(path, "READ"));
  if (!file || file->IsZombie()) {
    Error("plot_muon_stopping_distance", "cannot open %s", path);
    return;
  }

  auto *hist = file->Get<TH1>("muon_stopping_distance");
  if (!hist) {
    Error("plot_muon_stopping_distance",
          "no 'muon_stopping_distance' histogram in %s; re-run the simulation",
          path);
    return;
  }
  // Detach from the file so the histogram survives the file closing
  hist->SetDirectory(nullptr);

  // Older outputs stored "title;x;y" verbatim. Re-setting the title lets ROOT
  // split it into axis titles.
  const TString title = hist->GetTitle();
  if (title.Contains(";")) {
    hist->SetTitle(title);
  }

  const double entries = hist->GetEntries();
  if (entries == 0) {
    Warning("plot_muon_stopping_distance",
            "'muon_stopping_distance' in %s is empty", path);
  }

  // Overflow means muons stopped past the histogram range (deeper than it
  // covers); widen the range in RunAction if this is non-zero.
  const int nBins = hist->GetNbinsX();
  const double underflow = hist->GetBinContent(0);
  const double overflow = hist->GetBinContent(nBins + 1);
  if (overflow > 0) {
    Warning("plot_muon_stopping_distance",
            "%.0f entries overflow the %.2f mm histogram range", overflow,
            hist->GetXaxis()->GetXmax());
  }

  // Most probable depth and FWHM of the range peak
  const int peakBin = hist->GetMaximumBin();
  const double peak = hist->GetBinCenter(peakBin);
  const double half = 0.5 * hist->GetBinContent(peakBin);
  const double fwhm =
      crossing(hist, peakBin, +1, half) - crossing(hist, peakBin, -1, half);

  std::printf("muon_stopping_distance in %s\n", path);
  std::printf("  entries        %.0f (underflow %.0f, overflow %.0f)\n",
              entries, underflow, overflow);
  std::printf("  mean depth     %.4f mm\n", hist->GetMean());
  std::printf("  std dev        %.4f mm\n", hist->GetStdDev());
  std::printf("  peak depth     %.4f mm\n", peak);
  std::printf("  FWHM           %.4f mm\n", fwhm);

  gStyle->SetOptStat("emruo");

  auto *canvas = new TCanvas("c_muon_stopping_distance",
                             "Muon stopping depth", 900, 650);
  canvas->SetLogy(logy);
  canvas->SetGrid();
  // Room for the y title next to the x10^N exponent on a linear axis
  canvas->SetLeftMargin(0.13);
  hist->GetYaxis()->SetTitleOffset(1.4);

  // The histogram spans the full target; zoom to where muons actually stop
  if (entries > 0) {
    const int first = hist->FindFirstBinAbove(0.0);
    const int last = hist->FindLastBinAbove(0.0);
    const int pad = std::max(2, (last - first) / 10);
    hist->GetXaxis()->SetRange(std::max(1, first - pad),
                               std::min(nBins, last + pad));
  }

  hist->SetLineColor(kAzure + 2);
  hist->SetLineWidth(2);
  hist->Draw("HIST");
  canvas->Update();

  if (entries > 0) {
    double ylo = canvas->GetUymin();
    double yhi = canvas->GetUymax();
    if (logy) {
      ylo = std::pow(10.0, ylo);
      yhi = std::pow(10.0, yhi);
    }
    auto *peakLine = new TLine(peak, ylo, peak, yhi);
    peakLine->SetLineStyle(2);
    peakLine->SetLineColor(kRed + 1);
    peakLine->Draw();

    auto *label = new TLatex();
    label->SetNDC();
    label->SetTextSize(0.035);
    label->SetTextColor(kRed + 1);
    label->DrawLatex(0.17, 0.84, Form("peak = %.3f mm", peak));
    if (!std::isnan(fwhm)) {
      label->DrawLatex(0.17, 0.79, Form("FWHM = %.3f mm", fwhm));
    }
  }

  canvas->Update();
}
