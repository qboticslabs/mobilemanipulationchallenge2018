#include <dynamic_introspection/DynamicIntrospection.h>
#include <dynamic_introspection/BoolParameter.h>
#include <dynamic_introspection/DoubleParameter.h>
#include <dynamic_introspection/IntParameter.h>
#include <dynamic_introspection/VectorParameter.h>
#include <dynamic_introspection/MatrixParameter.h>

void copyEigenVector2Message(const Eigen::VectorXd &in, dynamic_introspection::VectorParameter &out){
 assert(in.rows() == out.value.size());
 for(unsigned int i=0; i<in.rows(); ++i){
   out.value[i] = in(i);
 }

}

void copyEigenMatrix2Message(const Eigen::MatrixXd &in, dynamic_introspection::MatrixParameter &out){
  assert(in.rows() == out.rows);
  assert(in.cols() == out.cols);
  assert(in.rows()*in.cols() == out.value.size());

  for(unsigned int i=0; i<in.rows(); ++i){
    for(unsigned int j=0; j<in.cols(); ++j){
      out.value[j + in.rows()*i] = in(i,j);
    }
  }
}

DynamicIntrospection::DynamicIntrospection(ros::NodeHandle &nh, const std::string &topic):
  node_handle_(nh), configured_(false), openedBag_(false){
  introspectionPub_ =  nh.advertise<dynamic_introspection::IntrospectionMsg>(topic, 10);
}

DynamicIntrospection::~DynamicIntrospection(){
  closeBag();
}

void DynamicIntrospection::openBag(std::string fileName){
  bag_.open(fileName, rosbag::bagmode::Write);
  openedBag_ = true;
}

void DynamicIntrospection::closeBag(){
  bag_.close();
  openedBag_ = false;
}

void DynamicIntrospection::publishDataBag(){
  if(!openedBag_){
    ROS_ERROR_STREAM("Bag is not open");
  }
  generateMessage();
  bag_.write("dynamic_introspection", ros::Time::now(), introspectionMessage_);
}

void DynamicIntrospection::publishDataTopic(){
  generateMessage();
  introspectionPub_.publish(introspectionMessage_);
}

void DynamicIntrospection::generateMessage(){

  introspectionMessage_.ints.resize(registeredInt_.size());
  introspectionMessage_.doubles.resize(registeredDouble_.size());
  introspectionMessage_.bools.resize(registeredBool_.size());
  introspectionMessage_.vectors.resize(registeredVector_.size());
  introspectionMessage_.matrixs.resize(registeredMatrix_.size());

  for(unsigned int i=0; i<registeredVector_.size(); ++i){
    introspectionMessage_.vectors[i].value.resize(registeredVector_[i].second->rows());
  }

  for(unsigned int i=0; i<registeredMatrix_.size(); ++i){
    introspectionMessage_.matrixs[i].value.resize(registeredMatrix_[i].second->rows()*registeredMatrix_[i].second->cols());
  }

  for(unsigned int i=0; i<registeredInt_.size(); ++i){
    dynamic_introspection::IntParameter &ip = introspectionMessage_.ints[i];
    ip.name = registeredInt_[i].first;
    ip.value = *registeredInt_[i].second;
  }

  for(unsigned int i=0; i<registeredDouble_.size(); ++i){
    dynamic_introspection::DoubleParameter &dp = introspectionMessage_.doubles[i];
    dp.name = registeredDouble_[i].first;
    dp.value = *registeredDouble_[i].second;
  }

  for(unsigned int i=0; i<registeredBool_.size(); ++i){
    dynamic_introspection::BoolParameter &bp = introspectionMessage_.bools[i];
    bp.name = registeredBool_[i].first;
    bp.value = *registeredBool_[i].second;
  }

  for(unsigned int i=0; i<registeredVector_.size(); ++i){
    dynamic_introspection::VectorParameter &vp = introspectionMessage_.vectors[i];
    vp.name = registeredVector_[i].first;
    vp.value.resize(registeredVector_[i].second->rows());
    copyEigenVector2Message(*registeredVector_[i].second, vp);
  }

  for(unsigned int i=0; i<registeredMatrix_.size(); ++i){
    dynamic_introspection::MatrixParameter &mp = introspectionMessage_.matrixs[i];
    mp.name = registeredMatrix_[i].first;
    mp.rows = registeredMatrix_[i].second->rows();
    mp.cols =  registeredMatrix_[i].second->cols();
    mp.value.resize(mp.rows*mp.cols);
    copyEigenMatrix2Message(*registeredMatrix_[i].second, mp);
  }
}

void DynamicIntrospection::registerVariable(int *variable, std::string id){
  ROS_DEBUG_STREAM("Registered int");
  std::pair<std::string, int*> p(id, variable);
  registeredInt_.push_back(p);
}

void DynamicIntrospection::registerVariable(double *variable, std::string id){
  ROS_DEBUG_STREAM("Registered double");
  std::pair<std::string, double*> p(id, variable);
  registeredDouble_.push_back(p);
}

void DynamicIntrospection::registerVariable(bool *variable, std::string id){
  ROS_DEBUG_STREAM("Registered bool");
  std::pair<std::string, bool*> p(id, variable);
  registeredBool_.push_back(p);
}

void DynamicIntrospection::registerVariable(Eigen::VectorXd *variable, std::string id){
  ROS_DEBUG_STREAM("Registered Vector");
  std::pair<std::string, Eigen::VectorXd*> p(id, variable);
  registeredVector_.push_back(p);
}

void DynamicIntrospection::registerVariable(Eigen::MatrixXd *variable, std::string id){
  ROS_DEBUG_STREAM("Registered Matrix");
  std::pair<std::string, Eigen::MatrixXd*> p(id, variable);
  registeredMatrix_.push_back(p);
}
