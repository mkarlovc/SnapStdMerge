#include "stdafx.h"

int main(int argc, char* argv[]) {
  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("Network community detection. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
  TExeTm ExeTm;
  Try
  const TStr InFNm = Env.GetIfArgPrefixStr("-i:", "../evo/", "Input graph (undirected graph)");
  const double alpha = Env.GetIfArgPrefixFlt("-alpha:", 0.6, "alpha");
  const double beta = Env.GetIfArgPrefixFlt("-beta:", 0.6, "beta");
  const int CmtyAlg = Env.GetIfArgPrefixInt("-a:", 2, "Algorithm: 1:Girvan-Newman, 2:Clauset-Newman-Moore, 3:Infomap");

  double Q = 0.0;
  TStr CmtyAlgStr;
  if (CmtyAlg == 1) {
	CmtyAlgStr = "Girvan-Newman"; }
  else if (CmtyAlg == 2) {
    CmtyAlgStr = "Clauset-Newman-Moore"; }
  else if (CmtyAlg == 3) {
    CmtyAlgStr = "Infomap"; }
  else { Fail; }

  TVec<PUNGraph, TSize> gs;
  PNGraph outGraph = TNGraph::New(); // output directed graph off community evolution

  TIntH t; //time
  TIntH c; //community mapping
  TIntH s; //sizes
  TIntV e; //edges
  TIntIntVH m; //members original id

  if (CmtyAlg > 0 && CmtyAlg <= 3) {
    TSnap::LoadGraphArray(InFNm, gs);
    TSnap::CmtyEvolutionBatchGraph(gs, outGraph, t, c, s, e, m, alpha, beta, CmtyAlg);
  }

  printf("\n%i Input graphs:\n", gs.Len());
  for (int i=0; i<gs.Len(); i++) {
    printf("%i. #Nodes: %d    Edges: %d\n", i+1, gs[i]->GetNodes(), gs[i]->GetEdges());
  }

  printf("\nOutput directed community evolution graph: #Nodes: %i	#Edges: %i\n", outGraph->GetNodes(), outGraph->GetEdges());
  if (outGraph->GetNodes()>0) {
    printf("Source(time, size)\tDestination(time,size)\n");
  }
  for (TNGraph::TEdgeI EI=outGraph->BegEI(); EI != outGraph->EndEI(); EI++) {
	  printf("%i(%i, %i)\t%i(%i,%i)\n", EI.GetSrcNId(), t.GetDat(EI.GetSrcNId()), s.GetDat(EI.GetSrcNId()), EI.GetDstNId(), t.GetDat(EI.GetDstNId()), s.GetDat(EI.GetDstNId()));
  }

  // Create and print JSON string of the communty evolution graph
  TIntStrH txt;
  TStr json_string = TSnap::CmtyEvolutionGraphToJson(outGraph,t,c,s,e,txt);
  FILE *F = fopen("json_str.txt", "wt");
  fprintf(F, "%s", json_string.CStr());
  fclose(F);

  Catch
  printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
  return 0;
}