#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/SVD>

#include <iostream>

class Student {
  public:
    // typedef Transform<double,3,Isometry> Isometry3d;
    const Eigen::Isometry3d& tr_cam2veh() const { return _Tr_cam2veh; }

    Eigen::Vector3d opticalCenter() const { return _Tr_cam2veh.matrix().block(0, 3, 0, 3); }

  private:
    Eigen::Isometry3d _Tr_cam2veh = Eigen::Isometry3d::Identity();
};

int main() {
    Student st;
    std::cout << st.tr_cam2veh().matrix() << std::endl;
    std::cout << st.opticalCenter() << std::endl;

    return 0;
}
