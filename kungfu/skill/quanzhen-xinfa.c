// quanzhen-xinfa.c ȫ���ķ�

inherit FORCE;

int valid_enable(string usage) 
{ return usage == "force"; }



int practice_skill(object me)
{
        return notify_fail("ȫ���ķ�ֻ�ܿ��������ϰ��\n");
}

string exert_function_file(string func)
{
        return __DIR__"quanzhen-xinfa/" + func;
}