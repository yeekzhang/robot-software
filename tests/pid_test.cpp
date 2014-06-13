#include "CppUTest/TestHarness.h"

extern "C" {
#include "../pid.h"
}

TEST_GROUP(PIDTestGroup)
{
    pid_filter_t *pid;
    float output;

    void setup(void)
    {
        pid = pid_create();
    }

    void teardown(void)
    {
        pid_delete(pid);
    }
};

TEST(PIDTestGroup, IntegralValueIsZeroAtInit)
{
    CHECK_EQUAL(0, pid_get_integral(pid));
}

TEST(PIDTestGroup, PControllerAtInit)
{
    CHECK_EQUAL(1., pid_get_kp(pid));
    CHECK_EQUAL(0., pid_get_ki(pid));
    CHECK_EQUAL(0., pid_get_kd(pid));
}

TEST(PIDTestGroup, CanSetGains)
{
    pid_set_gains(pid, 10., 20., 30.);
    CHECK_EQUAL(10., pid_get_kp(pid));
    CHECK_EQUAL(20., pid_get_ki(pid));
    CHECK_EQUAL(30., pid_get_kd(pid));
}

TEST(PIDTestGroup, ZeroErrorMakesForZeroOutput)
{
    output = pid_process(pid, 0.);
    CHECK_EQUAL(0, output);
}

TEST(PIDTestGroup, ByDefaultIsIdentity)
{
    output = pid_process(pid, 42.);
    CHECK_EQUAL(42., output);
}

TEST(PIDTestGroup, KpHasInfluenceOnOutput)
{
    pid_set_gains(pid, 2., 0., 0.);
    output = pid_process(pid, 21.);
    CHECK_EQUAL(42., output);
}

TEST(PIDTestGroup, IntegratorIsChangedByProcess)
{
    pid_process(pid, 42.);
    CHECK_EQUAL(42., pid_get_integral(pid));

    pid_process(pid, 42.);
    CHECK_EQUAL(84., pid_get_integral(pid));
}

TEST(PIDTestGroup, AddingKiMakesOutputIncrease)
{
    pid_set_gains(pid, 0., 2., 0.);
    DOUBLES_EQUAL(2*42., pid_process(pid, 42.), 1e-3);
    DOUBLES_EQUAL(2*84., pid_process(pid, 42.), 1e-3);
}

TEST(PIDTestGroup, AddingKdCreatesDerivativeAction)
{
    pid_set_gains(pid, 0., 0., 2.);
    DOUBLES_EQUAL(84., pid_process(pid, 42.), 1e-3);
    DOUBLES_EQUAL(0., pid_process(pid, 42.), 1e-3);
}

