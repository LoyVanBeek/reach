#ifndef MOVEIT_REACH_PLUGINS_IK_MOVEIT_IK_SOLVER_H
#define MOVEIT_REACH_PLUGINS_IK_MOVEIT_IK_SOLVER_H

#include <reach/plugins/ik_solver_base.h>
#include <reach/plugins/evaluation_base.h>
#include <pluginlib/class_loader.h>

namespace moveit
{
namespace core
{
class RobotModel;
typedef std::shared_ptr<const RobotModel> RobotModelConstPtr;
class JointModelGroup;
class RobotState;
}
}

namespace planning_scene
{
class PlanningScene;
typedef std::shared_ptr<PlanningScene> PlanningScenePtr;
}

namespace moveit_reach_plugins
{
namespace ik
{

class MoveItIKSolver : public reach::plugins::IKSolverBase
{
public:

  MoveItIKSolver();

  virtual bool initialize(XmlRpc::XmlRpcValue& config) override;

  virtual boost::optional<double> solveIKFromSeed(const Eigen::Isometry3d& target,
                                                  const std::map<std::string, double> &seed,
                                                  std::vector<double> &solution) override;

  virtual std::vector<std::string> getJointNames() const override;

protected:

  bool isIKSolutionValid(moveit::core::RobotState* state,
                         const moveit::core::JointModelGroup* jmg,
                         const double* ik_solution) const;

  moveit::core::RobotModelConstPtr model_;

  planning_scene::PlanningScenePtr scene_;

  const moveit::core::JointModelGroup* jmg_;

  pluginlib::ClassLoader<reach::plugins::EvaluationBase> class_loader_;

  reach::plugins::EvaluationBasePtr eval_;

  double distance_threshold_;

  std::string collision_mesh_filename_;

  std::string collision_mesh_frame_;

  std::vector<std::string> touch_links_;
};

} // namespace ik
} // namespack moveit_reach_plugins

#endif // MOVEIT_REACH_PLUGINS_IK_MOVEIT_IK_SOLVER_H
