// tianmogong.c ��ħ��

inherit FORCE;
#include "force.h"
int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
                if ( userp(me) )
                return notify_fail("ѧ��ħ����Ҫ�ĺ���������������������ò���ѽ��\n");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("��ħ��ֻ����ѧ(learn)�������������ȡ�\n");
}