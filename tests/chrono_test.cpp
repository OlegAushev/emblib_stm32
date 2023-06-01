#include <emblib_stm32/tests/tests.h>


void emb::tests::chrono_test() {
#ifdef EMB_TESTS_ENABLED
    emb::chrono::seconds sec(10);
    EMB_ASSERT_EQUAL(sec.count(), 10);
    emb::chrono::milliseconds msec = emb::chrono::duration_cast<emb::chrono::milliseconds>(sec);
    EMB_ASSERT_EQUAL(msec.count(), 10000);
    EMB_ASSERT_EQUAL(msec, emb::chrono::milliseconds(10000));

    emb::chrono::microseconds usec = emb::chrono::duration_cast<emb::chrono::microseconds>(sec);
    EMB_ASSERT_EQUAL(usec.count(), 10000000);

    emb::chrono::nanoseconds nsec = emb::chrono::duration_cast<emb::chrono::nanoseconds>(usec);
    EMB_ASSERT_EQUAL(nsec.count(), 10000000000);

    EMB_ASSERT_EQUAL(msec - emb::chrono::milliseconds(1), emb::chrono::milliseconds(9999));

    emb::chrono::milliseconds msec2 = msec + emb::chrono::milliseconds(1);
    EMB_ASSERT_EQUAL(msec2.count(), 10001);

    EMB_ASSERT_TRUE(msec2 > msec);

    EMB_ASSERT_TRUE(emb::chrono::microseconds(2) > emb::chrono::microseconds(1));
    EMB_ASSERT_TRUE(emb::chrono::microseconds(2) >= emb::chrono::microseconds(2));
    EMB_ASSERT_TRUE(emb::chrono::microseconds(1) < emb::chrono::microseconds(2));
    EMB_ASSERT_TRUE(emb::chrono::microseconds(2) <= emb::chrono::microseconds(2));
    EMB_ASSERT_TRUE(emb::chrono::microseconds(1) == emb::chrono::microseconds(1));
    EMB_ASSERT_TRUE(emb::chrono::microseconds(1) != emb::chrono::microseconds(2));

    emb::chrono::seconds sec2 = ++sec;
    EMB_ASSERT_EQUAL(sec.count(), 11);
    EMB_ASSERT_EQUAL(sec2.count(), 11);

    emb::chrono::seconds sec3 = sec++;
    EMB_ASSERT_EQUAL(sec.count(), 12);
    EMB_ASSERT_EQUAL(sec3.count(), 11);

    emb::chrono::seconds sec4 = --sec;
    EMB_ASSERT_EQUAL(sec.count(), 11);
    EMB_ASSERT_EQUAL(sec4.count(), 11);

    emb::chrono::seconds sec5 = sec--;
    EMB_ASSERT_EQUAL(sec.count(), 10);
    EMB_ASSERT_EQUAL(sec5.count(), 11);
#endif
}

