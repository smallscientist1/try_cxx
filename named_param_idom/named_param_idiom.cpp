#include <iostream>
template <typename Base, int D>
class Discriminator : public Base {

};

template <typename Setter1, typename Setter2, typename Setter3, typename Setter4>
class PolicySelector:
    public Discriminator<Setter1, 1>,
    public Discriminator<Setter2, 2>,
    public Discriminator<Setter3, 3>,
    public Discriminator<Setter4, 4>
{
    // 不同直接继承Setter1, Setter2, Setter3, Setter4, 因为当Setter1, Setter2相同时,会因为继承相同的类编译出错
};

class INSTANCE1{
public:
    constexpr static int value = 1;
};
class INSTANCE2{
public:
    constexpr static int value = 2;
};
class INSTANCE3{
public:
    constexpr static int value = 3;
};
class INSTANCE4{
public:
    constexpr static int value = 4;
};

class DefaultPolicies {
public:
    typedef INSTANCE1 P1;
    typedef INSTANCE2 P2;
    typedef INSTANCE3 P3;
    typedef INSTANCE4 P4;
};
// 用于使用缺省policy的类
// 虚继承是为了多次派生自DefaultPolicies时出现二义性???
class DefaultPolicyArgs : virtual public DefaultPolicies {};


template <typename Policy>
class Policy1_is: virtual public DefaultPolicies {// 虚继承是为了多次派生自DefaultPolicies时出现二义性???
public:
    typedef Policy P1;
};
template <typename Policy>
class Policy2_is: virtual public DefaultPolicies {
public:
    typedef Policy P2;
};
template <typename Policy>
class Policy3_is: virtual public DefaultPolicies {
public:
    typedef Policy P3;
};
template <typename Policy>
class Policy4_is: virtual public DefaultPolicies {
public:
    typedef Policy P4;
};

template <typename I1 = DefaultPolicyArgs, typename I2 = DefaultPolicyArgs, typename I3 = DefaultPolicyArgs, typename I4 = DefaultPolicyArgs>
class Myclass {
    typedef PolicySelector<I1, I2, I3, I4> Policies;
    public:
    constexpr static int i1 = Policies::P1::value;
    constexpr static int i2 = Policies::P2::value;
    constexpr static int i3 = Policies::P3::value;
    constexpr static int i4 = Policies::P4::value;
};

int main() {
    Myclass<> m0;
    std::cout << m0.i1 << " " << m0.i2 << " " << m0.i3 << " " << m0.i4 << std::endl;
    Myclass<Policy2_is<INSTANCE3>> m1;
    std::cout << m1.i1 << " " << m1.i2 << " " << m1.i3 << " " << m1.i4 << std::endl;
    return 0;
}
