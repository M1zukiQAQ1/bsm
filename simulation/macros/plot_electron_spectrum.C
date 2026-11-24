// Draw the mu- decay-in-orbit electron spectrum written by muonB10.
//
// Run from the directory that holds the output file (e.g. simulation/):
//   root -l macros/plot_electron_spectrum.C
//   root -l 'macros/plot_electron_spectrum.C("path/to/muon_stopping.root")'
//   root -l 'macros/plot_electron_spectrum.C("muon_stopping.root", false)'  //
//   linear y

#include <TCanvas.h>
#include <TError.h>
#include <TFile.h>
#include <TH1.h>
#include <TLatex.h>
#include <TLine.h>
#include <TStyle.h>

#include <cmath>
#include <memory>

void plot_electron_spectrum(const char *path = "muon_stopping.root",
                            bool logy = true) {
  std::unique_ptr<TFile> file(TFile::Open(path, "READ"));
  if (!file || file->IsZombie()) {
    Error("plot_electron_spectrum", "cannot open %s", path);
    return;
  }

  auto *hist = file->Get<TH1>("electron_spectrum");
  if (!hist) {
    Error("plot_electron_spectrum",
          "no 'electron_spectrum' histogram in %s; re-run the simulation",
          path);
    return;
  }
  // Detach from the file so the histogram survives the file closing
  hist->SetDirectory(nullptr);

  if (hist->GetEntries() == 0) {
    Warning("plot_electron_spectrum", "'electron_spectrum' in %s is empty",
            path);
  }

  gStyle->SetOptStat("emruo");

  auto *canvas =
      new TCanvas("c_electron_spectrum", "Electron spectrum", 900, 650);
  canvas->SetGrid();

  hist->SetLineColor(kAzure + 2);
  hist->SetLineWidth(2);
  hist->Draw("HIST");
  canvas->Update();

  // Free mu- decay endpoint in kinetic energy: (m_mu^2 + m_e^2) / 2 m_mu - m_e.
  // Decay-in-orbit electrons reach past it because the bound muon is moving.
  const double michelEdge = 52.32; // MeV
  double ylo = canvas->GetUymin();
  double yhi = canvas->GetUymax();
  if (logy) {
    ylo = std::pow(10.0, ylo);
    yhi = std::pow(10.0, yhi);
  }
  auto *edge = new TLine(michelEdge, ylo, michelEdge, yhi);
  edge->SetLineStyle(2);
  edge->SetLineColor(kRed + 1);
  edge->Draw();

  auto *label = new TLatex(michelEdge + 1.0, logy ? ylo * 2.0 : yhi * 0.05,
                           "free #mu decay endpoint");
  label->SetTextSize(0.03);
  label->SetTextColor(kRed + 1);
  label->Draw();

  canvas->Update();
}
