#include <iostream>
#include <vector>
#include "Math/SMatrix.h"
#include "Math/SVector.h"
#include "TRandom3.h"
#include "TFile.h"
#include "TH1F.h"
#include "SimpleParamParser.h"




double SimpleProdErr(double f, std::vector<double> x, std::vector<double> x_e) {
  double sum = 0.0;
  if (x.size() != x_e.size()) {
    std::cerr << "Vectors have different size!" << std::endl;
    return 0.0;
  }
  for (unsigned i = 0; i < x.size(); ++i) {
    sum += (x_e[i]/x[i])*(x_e[i]/x[i]);
  }
  if (sum <= 0.0) {
    std::cout << "Error, sum is " << sum << std::endl;
    return 0.0;
  } else {
    sum = sqrt(sum);
    sum = f * sum;
    return sum;
  }
}

double SimpleSumErr(std::vector<double> x_e) {
  double sum = 0.0;
  for (unsigned i = 0; i < x_e.size(); ++i) {
    sum += x_e[i]*x_e[i];
  }
  return sqrt(sum);
}


int main(int argc, char* argv[]){
  std::cout << "Arguments passed to program: " << argc << std::endl;
  for (int i = 0; i < argc; ++i){
    std::cout << i << "\t" << argv[i] << std::endl;
  }
  typedef ROOT::Math::SMatrix<double,2>                                       SMatrix22;
  typedef ROOT::Math::SVector<double,2>                                       SVector2; 

  TRandom3 rand;
  TFile f("output.root","RECREATE");
  TH1F h_N1("N1","N1",100,11000,13000);
  TH1F h_N2("N2","N2",100,1000,2000);

 
  SimpleParamParser input;
  input.ParseFile("ee.dat");
  double N_TAG_1 = input.GetParam<double>("N_TAG_1");
  std::cout << N_TAG_1 << std::endl;
  double N_TAG_1_err = input.GetParam<double>("N_TAG_1_err");
  double N_TAG_2 = input.GetParam<double>("N_TAG_2");
    std::cout << N_TAG_2 << std::endl;

  double N_TAG_2_err = input.GetParam<double>("N_TAG_2_err");
  double p_1  = input.GetParam<double>("p_1");
  double p_21 = input.GetParam<double>("p_21");
  double p_22 = input.GetParam<double>("p_22");
  double p_2;
  double ftt_1 = input.GetParam<double>("ftt_1");
  double ftt_2 = input.GetParam<double>("ftt_2");
  double N_RTAG_1, N_RTAG_1_err, N_RTAG_2, N_RTAG_2_err;
  double e_b_11 =  input.GetParam<double>("e_b_11");
  double e_b_11_err = input.GetParam<double>("e_b_11_err");
  double e_b_21 = input.GetParam<double>("e_b_21"); 
  double e_b_21_err = input.GetParam<double>("e_b_21_err");
  double e_b_22 = input.GetParam<double>("e_b_22");
  double e_b_22_err = input.GetParam<double>("e_b_22_err");
  double e_l_1 = input.GetParam<double>("e_l_1");
  double e_l_1_err = input.GetParam<double>("e_l_1_err");
  double e_l_2 = input.GetParam<double>("e_l_2");
  double e_l_2_err = input.GetParam<double>("e_l_2_err");
  double e_r_11 = input.GetParam<double>("e_r_11");
  double e_r_11_err = input.GetParam<double>("e_r_11_err");
  double e_r_21 = input.GetParam<double>("e_r_21");
  double e_r_21_err = input.GetParam<double>("e_r_21_err");
  double e_r_12 = input.GetParam<double>("e_r_12");
  double e_r_12_err = input.GetParam<double>("e_r_12_err");
  double e_r_22 = input.GetParam<double>("e_r_22");
  double e_r_22_err = input.GetParam<double>("e_r_22_err");
  double e_r_01 = input.GetParam<double>("e_r_01");
  double e_r_01_err = input.GetParam<double>("e_r_01_err");
  double e_r_02 = input.GetParam<double>("e_r_02");
  double e_r_02_err = input.GetParam<double>("e_r_02_err");
  double R = input.GetParam<double>("R");
  double a_l_1 = input.GetParam<double>("a_l_1");
  double a_l_1_err = input.GetParam<double>("a_l_1_err");
  double a_l_2 = input.GetParam<double>("a_l_2");
  double a_l_2_err = input.GetParam<double>("a_l_2_err");

  for (unsigned i = 0; i < 1000000; ++i) {
    p_2           = p_21 * p_22;
    N_RTAG_1         = N_TAG_1 * (p_1 - ftt_1);
    if (i == 0) std::cout << p_2 << std::endl;
    N_RTAG_1_err       = 23.0;
    N_RTAG_2         = N_TAG_2 * (p_2 - ftt_2);
    N_RTAG_2_err       = 5.0;
  

    /*
    N_T_1         = 1918.0;
    N_T_1_err       = 30;
    N_T_2         = 97.0;
    N_T_2_err       = 0.0001;
    */

    /*
    N_T_1         = 3079.0;
    N_T_1_err       = 23.0;
    N_T_2         = 151.0;
    N_T_2_err       = 5.0;
    */


  if (i > 0) {
    N_RTAG_1 = rand.Gaus(N_RTAG_1, N_RTAG_1_err);
    N_RTAG_2 = rand.Gaus(N_RTAG_2, N_RTAG_2_err);
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


  double N_T_arr[] = { N_RTAG_1, 
                       N_RTAG_2 };

  double ep_b_arr[] = {   1.0/e_b_11  ,  -1.0 * e_b_21/(e_b_22*e_b_11),
                          0.0         ,  1.0/(e_b_22)   };

  double ep_l_arr[] = {   1.0/e_l_1 ,  0.0,
                          0.0       ,  1.0/e_l_2   };

  double ep_r_arr[] = {   e_r_11 + R*e_r_01 ,  e_r_21 + R*e_r_01,
                          e_r_12 + R*e_r_02 ,  e_r_22 + R*e_r_02   };

  double A_l_arr[] =  {   1.0/a_l_1 ,  0.0,
                          0.0       ,  1.0/a_l_2   };

  SVector2 N_T(N_T_arr,2);
  SMatrix22 ep_b(ep_b_arr,4);
  SMatrix22 ep_l(ep_l_arr,4);
  SMatrix22 ep_r(ep_r_arr,4);
  SMatrix22  A_l(A_l_arr,4);

  if (i ==0) {
    std::cout << "N_T (initial tagged): \n" << N_T << std::endl;
    std::cout << "ep_b:\n" << ep_b << std::endl;
    std::cout << "ep_l:\n" << ep_l << std::endl;
    std::cout << "ep_r:\n" << ep_r << std::endl;
  }
  ep_r.Invert();
  if (i == 0) {
    std::cout << "ep_r_inv:\n" << ep_r << std::endl;
    std::cout << "A_l:\n" << A_l << std::endl;
  }
  N_T = ep_b * N_T;
  if (i == 0) std::cout << "N_B (after e_b):\n" << N_T << std::endl;
  N_T = ep_l * N_T;
  if (i == 0)std::cout << "N_L (after e_l):\n" << N_T << std::endl;
  N_T = ep_r * N_T;
  if (i == 0)std::cout << "N_R (after e_r):\n" << N_T << std::endl;
  N_T = A_l * N_T;
  if (i == 0)std::cout << "N_A (after A_l):\n" << N_T << std::endl;

  if (i > 0) {
    h_N1.Fill(N_T[0]);
    h_N2.Fill(N_T[1]);
  }

  }



  f.cd();
  h_N1.Write();
  h_N2.Write();
  f.Close();
  
  return 0;
}


   