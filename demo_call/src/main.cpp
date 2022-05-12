/// 测试vcpkg安装的库的cmake调用方法

/// dlib
/// introduce
/// 基于契约和组件的编程:每个组件有大量文档和完整调试模式
/// 涉及：networking, threads, graphical interfaces, complex data structures, linear algebra, statistical machine learning, image processing, data mining, XML and text parsing, numerical optimization, Bayesian networks, and numerous other tasks
/// 哲学：易用行，不需要安装其他，平台特异性不允许出现在api。支持OS X, MS Windows, Linux, Solaris, the BSDs, and HP-UX平台
#include <dlib/gui_widgets.h>
#include <dlib/image_transforms.h>
#include <cmath>

using namespace dlib;
using namespace std;

///////////////// dlib::noncopyable ///////////////////////

/// noncopyable 的实现方法是将拷贝构造函数声明为private
/// 从而在外部调用时会编译失败
/// 但是如果将其重新声明为public会怎么样
/// 》虽然StructB通过继承基类dlib::noncopyable获得了不可拷贝属性，但是重新将拷贝构造函数重新声明为public会是拷贝重新有效
/// !无法重新声明，继承一个实基类，如何改变器private,protect,public 属性
/// 1.类的实例化对象不能访问protected成员函数和成员；
/// 2.类的成员函数可以访问protected的成员和private成员；
/// 3.只有在派生类中才可以通过派生类对象访问基类的protected成员
/// 派生类可以覆盖基类中的protected/private同名函数

#ifdef DEBUG_noncopyable
class StructA{
public:
    int __i;
};

class StructB:private dlib::noncopyable{
public:
    StructB()=default;
    int __i;
    StructB(const StructB& v_b){__i=v_b.__i;}
};
class StructC
{
public:
    int __i;


protected:
    StructC()=default;
private:
    void func(){
        std::cout<<"StructC::func"<<std::endl;
    }

};

class StructD:public StructC
{
public:
    int __i;
    StructD()=default;
    void func()
    {
        std::cout<<"StructD::func"<<std::endl;
    }


};

#endif

void noncopyable_test()
{
#ifdef DEBUG_noncopyable
    //        StructA a1;
    //        StructA a2=a1;

    //        StructC c1;

    StructB b1;
    b1.__i=78;
    StructB b2=b1;
    std::cout<<"b2.__i="<<b2.__i<<std::endl;

    //        StructD d1;
    //        d1.func();
#endif
    return;
}
///////////////////////////////////////////////////////////////////////////////


/// 改写显示一个二维图像，高斯分布

void gaussian_random_draw()
{
    std::vector<perspective_window::overlay_dot> points;
    dlib::rand rnd;
    for (double i = 0; i < 20; i+=0.001)
    {
        dlib::vector<double> temp(rnd.get_random_gaussian(),
                                  rnd.get_random_gaussian(),
                                  rnd.get_random_gaussian());
        rgb_pixel color = colormap_jet(i,0,20);
        points.push_back(perspective_window::overlay_dot(temp, color));
    }
    // Now finally display the point cloud.
    perspective_window win;
    win.set_title("perspective_window 3D point cloud");
    win.add_overlay(points);
    win.wait_until_closed();

}

void spiral_draw()
{
    // Let's make a point cloud that looks like a 3D spiral.
    /// 带颜色的点
    std::vector<perspective_window::overlay_dot> points;

    dlib::rand rnd;
    for (double i = 0; i < 20; i+=0.001)
    {
        // Get a point on a spiral
        ///这里的应该是标准的螺旋线上的点
        dlib::vector<double> val(sin(i),cos(i),i/4);
        std::cout<<"val:"<<val<<std::endl;

        // Now add some random noise to it
        /// 给螺旋线添加基于高斯分布的随机数
        dlib::vector<double> temp(rnd.get_random_gaussian(),
                                  rnd.get_random_gaussian(),
                                  rnd.get_random_gaussian());
        val += temp/20;

        // Pick a color based on how far we are along the spiral
        /// 根据点的位置给定颜色
        rgb_pixel color = colormap_jet(i,0,20);

        // And add the point to the list of points we will display
        points.push_back(perspective_window::overlay_dot(val, color));
    }

    // Now finally display the point cloud.
    perspective_window win;
    win.set_title("perspective_window 3D point cloud");
    win.add_overlay(points);
    win.wait_until_closed();
}


// ----------------------------------------------------------------------------------------

int main()
{
    gaussian_random_draw();

noncopyable_test();
return 0;

}

//  ----------------------------------------------------------------------------



