// xixin-dafa.c ���Ĵ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int i = (int)me->query_skill("xixin-dafa", 1);
        int t = 1, j;
        for (j = 1; j < i / 10; j++) t*= 2;
        if ((int)me->query_skill("force", 1) < 10)
                return 
           notify_fail("��Ļ����ڹ�����㣬����ѧ���Ĵ󷨡�\n");
        if (i > 10 && (int)me->query("shen") > t * 50)
               return notify_fail("ѧ���Ĵ�Ҫɱ���������Լ������񣬶�ɱ����ߣ��������ɱ�Ĳ���ѽ�������ˣ�\n");
        if ( me->query_skill("buddhism",1) || me->query_skill("tao",1) )
                return notify_fail("�����˱���ķ��ǲ���ѧϰ���Ĵ󷨵ģ�ֻ�з���ѧϰ����ķ���\n");
        if ( me->query_skill("hunyuan-yiqi",1) 
        || me->query_skill("huntian-qigong",1) 
        || me->query_skill("taiji-shengong",1) )
                return notify_fail("�㲻�ȷ��������ڹ�������ѧ�������½̵����Ĵ󷨣�\n");
        return 1;
 }

int practice_skill(object me)
{
        return notify_fail("���Ĵ�ֻ����ѧ(xue)�����������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"xixin-dafa/" + func;
}            
