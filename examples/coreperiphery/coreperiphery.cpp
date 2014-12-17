#include "stdafx.h"

int main(int argc, char* argv[]) {

  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("Network core/periphery. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
  TExeTm ExeTm; // for measuring execution time
  Try
  const TStr InFNmGraph = Env.GetIfArgPrefixStr("-i:", "graph.txt", "Input graph (undirected graph)");

  PUNGraph Graph;
  Graph = TSnap::LoadEdgeList<PUNGraph>(InFNmGraph);
  int C = 0.0;
  TIntIntH out;
  C = TSnap::FastCorePeriphery(Graph, out);
  printf("Number of core nodes: %i\n", C);
  printf("Core nodes: %i\n", C);
  for (THashKeyDatI<TInt, TInt> it = out.BegI();  !it.IsEnd(); it++) {
    if (it.GetDat() == 1) {
	  printf("%i\n", it.GetKey());
	}
  }

  Catch
  return 0;
}