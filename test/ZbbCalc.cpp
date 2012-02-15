#include <iostream>
#include <vector>
#include <string>
#include "Math/SMatrix.h"
#include "Math/SVector.h"
#include "TRandom3.h"
#include "TH1F.h"
#include "SimpleParamParser.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"

int main(int argc, char* argv[]){
  typedef ROOT::Math::SMatrix<double,2>                                       SMatrix22;
  typedef ROOT::Math::SVector<double,2>                                       SVector2; 

  std::string param_file;
  if (argc != 2) {
    std::cout << "Usage: ./ZbbCalc <parameter file>" << std::endl;
    exit(1);
  } else {
    param_file = argv[1];
  }

  TRandom3 rand;
  TH1F h_N1("N1","N1",100,10000,13000);
  TH1F h_N2("N2","N2",100,1000,2000);

  SimpleParamParser input;
  input.ParseFile(param_file);
  double x_N_TAG_1 = input.GetParam<double>("N_TAG_1");
  double N_TAG_1_err = input.GetParam<double>("N_TAG_1_err");
  double x_N_TAG_2 = input.GetParam<double>("N_TAG_2");
  double N_TAG_2_err = input.GetParam<double>("N_TAG_2_err");
  double N_TAG_1, N_TAG_2;
  double p_1  = input.GetParam<double>("p_1");
  double p_21 = input.GetParam<double>("p_21");
  double p_22 = input.GetParam<double>("p_22");
  double p_2;
  double ftt_1 = input.GetParam<double>("ftt_1");
  double ftt_2 = input.GetParam<double>("ftt_2");
  double N_RTAG_1, N_RTAG_2;
  double x_e_b_11 =  input.GetParam<double>("e_b_11");
  double e_b_11_err = input.GetParam<double>("e_b_11_err");
  double x_e_b_21 = input.GetParam<double>("e_b_21"); 
  double e_b_21_err = input.GetParam<double>("e_b_21_err");
  double x_e_b_22 = input.GetParam<double>("e_b_22");
  double e_b_22_err = input.GetParam<double>("e_b_22_err");
  double e_b_11, e_b_21, e_b_22;
  double x_e_l_1 = input.GetParam<double>("e_l_1");
  double e_l_1_err = input.GetParam<double>("e_l_1_err");
  double x_e_l_2 = input.GetParam<double>("e_l_2");
  double e_l_2_err = input.GetParam<double>("e_l_2_err");
  double e_l_1, e_l_2;
  double x_e_r_11 = input.GetParam<double>("e_r_11");
  double e_r_11_err = input.GetParam<double>("e_r_11_err");
  double x_e_r_21 = input.GetParam<double>("e_r_21");
  double e_r_21_err = input.GetParam<double>("e_r_21_err");
  double x_e_r_12 = input.GetParam<double>("e_r_12");
  double e_r_12_err = input.GetParam<double>("e_r_12_err");
  double x_e_r_22 = input.GetParam<double>("e_r_22");
  double e_r_22_err = input.GetParam<double>("e_r_22_err");
  double x_e_r_01 = input.GetParam<double>("e_r_01");
  double e_r_01_err = input.GetParam<double>("e_r_01_err");
  double x_e_r_02 = input.GetParam<double>("e_r_02");
  double e_r_02_err = input.GetParam<double>("e_r_02_err");
  double e_r_11, e_r_21, e_r_12, e_r_22, e_r_01, e_r_02;
  double R = input.GetParam<double>("R");
  double x_a_l_1 = input.GetParam<double>("a_l_1");
  double a_l_1_err = input.GetParam<double>("a_l_1_err");
  double x_a_l_2 = input.GetParam<double>("a_l_2");
  double a_l_2_err = input.GetParam<double>("a_l_2_err");
  double a_l_1, a_l_2;
  double lumi = input.GetParam<double>("lumi");
  double N1, N2;

  for (unsigned i = 0; i < 1000000; ++i) {
    p_2           = p_21 * p_22;

    N_TAG_1 = x_N_TAG_1;
    N_TAG_2 = x_N_TAG_2;
    e_b_11 = x_e_b_11;
    e_b_21 = x_e_b_21;
    e_b_22 = x_e_b_22;
    e_l_1 = x_e_l_1;
    e_l_2 = x_e_l_2;
    e_r_11 = x_e_r_11;
    e_r_21 = x_e_r_21;
    e_r_12 = x_e_r_12;
    e_r_22 = x_e_r_22;
    e_r_01 = x_e_r_01;
    e_r_02 = x_e_r_02;
    a_l_1 = x_a_l_1;
    a_l_2 = x_a_l_2;

  if (i > 0) {
    N_TAG_1 = rand.Gaus(N_TAG_1, N_TAG_1_err);
    N_TAG_2 = rand.Gaus(N_TAG_2, N_TAG_2_err);
    e_b_11 = rand.Gaus(e_b_11, e_b_11_err);
    e_b_21 = rand.Gaus(e_b_21, e_b_21_err);
    e_b_22 = rand.Gaus(e_b_22, e_b_22_err);
    e_l_1 = rand.Gaus(e_l_1, e_l_1_err);
    e_l_2 = rand.Gaus(e_l_2, e_l_2_err);
    e_r_11 = rand.Gaus(e_r_11, e_r_11_err);
    e_r_12 = rand.Gaus(e_r_12, e_r_12_err);
    e_r_21 = rand.Gaus(e_r_21, e_r_21_err);
    e_r_22 = rand.Gaus(e_r_22, e_r_22_err);
    e_r_01 = rand.Gaus(e_r_01, e_r_01_err);
    e_r_02 = rand.Gaus(e_r_02, e_r_02_err);
    a_l_1 = rand.Gaus(a_l_1, a_l_1_err);
    a_l_2 = rand.Gaus(a_l_2, a_l_2_err);
  }


  double N_T_arr[] = {  N_TAG_1, 
                        N_TAG_2 };
  SVector2 N_T(N_T_arr,2);

  if (i == 0) {
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "N_events (tagged) [Z+1b, Z+2b]: \n\t" << N_T << std::endl;
  }

  N_T[0]      = N_TAG_1 * (p_1 - ftt_1) 
  + N_TAG_2 * (p_22+p_21 - 2.*p_2);
  N_T[1]      = N_TAG_2 * (p_2 - ftt_2);
  

  double ep_b_arr[] = {   1.0/e_b_11  ,  -1.0 * e_b_21/(e_b_22*e_b_11),
                          0.0         ,  1.0/(e_b_22)   };

  double ep_l_arr[] = {   1.0/e_l_1 ,  0.0,
                          0.0       ,  1.0/e_l_2   };

  double ep_r_arr[] = {   e_r_11 + R*e_r_01 ,  e_r_21 + R*e_r_01,
                          e_r_12 + R*e_r_02 ,  e_r_22 + R*e_r_02   };

  double A_l_arr[] =  {   1.0/a_l_1 ,  0.0,
                          0.0       ,  1.0/a_l_2   };

  SMatrix22 ep_b(ep_b_arr,4);
  SMatrix22 ep_l(ep_l_arr,4);
  SMatrix22 ep_r(ep_r_arr,4);
  SMatrix22  A_l(A_l_arr,4);

  if (i ==0) {
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "epsilon_b Matrix:\n" << ep_b << std::endl;
    std::cout << "epsilon_l Matrix:\n" << ep_l << std::endl;
    std::cout << "epsilon_r/C_hadron Matrix:\n" << ep_r << std::endl;
  }
  ep_r.Invert();
  if (i == 0) {
    std::cout << "epsilon_r/C_hadron Matrix (inverted):\n" << ep_r << std::endl;
    std::cout << "Acceptance_l Matrix:\n" << A_l << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "N_events (after purity & f_tt): \n\t" << N_T << std::endl;
  }

  double total_before_ep_b = N_T[0] + N_T[1];
  N_T = ep_b * N_T;
  if (i == 0) std::cout << "N_events (after epsilon_b):\n\t" << N_T << std::endl;
  double total_before_ep_l = N_T[0] + N_T[1];
  N_T = ep_l * N_T;
  if (i == 0) std::cout << "N_events (after epsilon_l):\n\t" << N_T << std::endl;
  double total_before_c_had = N_T[0] + N_T[1];
  N_T = ep_r * N_T;
  if (i == 0) std::cout << "N_events (after epsilon_r/C_hadron):\n\t" << N_T << std::endl;
  double total_before_a_l = N_T[0] + N_T[1];
  N_T = A_l * N_T;
  double total_after_a_l = N_T[0] + N_T[1];
  if (i == 0)std::cout << "N_events (after Acceptance_l):\n\t" << N_T << std::endl;

  if (i > 0) {
    h_N1.Fill(N_T[0]);
    h_N2.Fill(N_T[1]);
  }

    if (i == 0) {
      N1 = N_T[0];
      N2 = N_T[1];
      std::cout << "-----------------------------------------------" << std::endl;
      std::cout << "Effective Z+1b inclusive e_b(HE): " << total_before_ep_b/total_before_ep_l << std::endl;
      std::cout << "Effective Z+1b inclusive e_l: " << total_before_ep_l/total_before_c_had << std::endl;
      std::cout << "Effective Z+1b inclusive C_had: " << total_before_c_had/total_before_a_l << std::endl;
      std::cout << "Effective Z+1b inclusive A_l: " << total_before_a_l/total_after_a_l << std::endl;
      std::cout << "-----------------------------------------------" << std::endl;
  }
  }

  TFitResultPtr h_N1_fit = h_N1.Fit("gaus","NSQ");
  double N1_err = h_N1_fit->Parameter(2);
  TFitResultPtr h_N2_fit = h_N2.Fit("gaus","NSQ");
  double N2_err = h_N2_fit->Parameter(2);
  double XS_1 = N1 / lumi;
  double XS_1_err = N1_err/lumi;
  double XS_2 = N2 / lumi;
  double XS_2_err = N2_err/lumi;
  std::cout << "XS [pb] (Z+1b Exclusive):\t" << XS_1 
            << " +/- " << XS_1_err << " (stat)" << std::endl;
  std::cout << "XS [pb] (Z+2b Inclusive):\t" << XS_2 
            << " +/- " << XS_2_err << " (stat)" << std::endl;

  return 0;
}


   