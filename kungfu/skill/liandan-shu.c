// liandan-shu.c

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("medicine", 1) < 100)
                return notify_fail("��ı�����������̫ǳ���޷������µ���������\n");

        return 1;
}
