// jiguan-shu.c

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("literate", 1) < 100)
                return notify_fail("你的读书写字造诣太浅，无法领会深奥的机关术。\n");

        return 1;
}
