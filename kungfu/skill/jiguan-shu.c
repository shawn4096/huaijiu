// jiguan-shu.c

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("literate", 1) < 100)
                return notify_fail("��Ķ���д������̫ǳ���޷������µĻ�������\n");

        return 1;
}
