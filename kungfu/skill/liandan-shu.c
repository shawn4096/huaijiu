// liandan-shu.c

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("medicine", 1) < 100)
                return notify_fail("你的本草术理造诣太浅，无法领会深奥的炼丹术。\n");

        return 1;
}
