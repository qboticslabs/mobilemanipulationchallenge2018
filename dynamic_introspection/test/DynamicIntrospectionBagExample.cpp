#include <ros/ros.h>
#include <dynamic_introspection/DynamicIntrospection.h>

int main(int argc, char **argv) {
  // Setup debugging rosconsole
  if(ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug)){
    ros::console::notifyLoggerLevelsChanged();
  }

  ros::init(argc, argv, "dynamic_introspection_test");

  ros::NodeHandle nh("dynamic_introspection_test");



  bool bool_test = false;

  DynamicIntrospection di(nh, "debug_test");

  di.registerVariable(&bool_test, "bool_test");

  Eigen::MatrixXd matrix_test(5,5);
  matrix_test.setIdentity();
  di.registerVariable(&matrix_test, "matrix_test");

  Eigen::VectorXd vector_test(5);
  vector_test.setRandom();
  di.registerVariable(&vector_test, "vector_test");

  Eigen::VectorXd vector_test2(5);
  vector_test2.setRandom();
  di.registerVariable(&vector_test2, "vector_test2");

  Eigen::VectorXd vector_test3(5);
  vector_test3.setRandom();
  di.registerVariable(&vector_test3, "vector_test3");

  ROS_INFO("Spinning node");

  di.openBag("test.bag");
  di.publishDataBag();
  di.closeBag();


  return 0;
}
