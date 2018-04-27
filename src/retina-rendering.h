#ifndef RETINA_RENDERING_H_
#define RETINA_RENDERING_H_

#include "biodynamo.h"

namespace bdm {

BDM_SIM_OBJECT(RetinaCell, bdm::Cell) {
  BDM_SIM_OBJECT_HEADER(RetinaCellExt, 1, color_);

 public:
  RetinaCellExt() : Base() {}
  RetinaCellExt(const std::array<double, 3>& position, double diameter,
                int color) {
    Base::position_[kIdx] = position;
    Base::diameter_[kIdx] = diameter;
    color_[kIdx] = color;
  }

 private:
  vec<int> color_;
};

// Define compile time parameter
template <typename Backend>
struct CompileTimeParam : public DefaultCompileTimeParam<Backend> {
  using AtomicTypes = VariadicTypedef<RetinaCell>;
};

inline int Simulate(int argc, const char** argv) {
  InitializeBioDynamo(argc, argv);

  Param::export_visualization_ = true;
  Param::visualize_sim_objects_["RetinaCell"] = {"color_"};

  // TODO read csv file and create retina cells
  RetinaCell cell({0, 0, 0}, 10, 0);
  ResourceManager<>::Get()->push_back(cell);

  // Run simulation for one timestep
  Scheduler<> scheduler;
  scheduler.Simulate(1);

  return 0;
}

}  // namespace bdm

#endif  // RETINA_RENDERING_H_
