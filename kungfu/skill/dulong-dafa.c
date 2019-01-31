//dulong-dafa.c

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

#include "/kungfu/skill/force.h"
#include <ansi.h>
/*

*/
int force_effect(string skill)
{	
	//�Կ�Ч���Ǵ�-3 -> 3���ֱ����������ص����˺��ᣬΨһһ�����⣬��jiuyin-zhengong������
	//��Ȼ������������Ч��
	//��ͬ�ڹ����ʵ��ڹ���������˵�Ч����dulong-dafa���������ڹ���
	//���Ե��ڹ��Կ������Ч���ͺã����������ڹ����޷��Կ�����Ҫ�����˺�
	//û���г������ڹ������������ڹ����޷������ˡ�:(
        switch (skill)
        {
                case "jiuyang-shengong" : return 4;
                case "yijin-jing"       : return 3;
                case "huntian-qigong"   : return 3;
                case "qiantian-yiyang"  : return 3;
                case "yinyun-ziqi"      : return 2;
                case "zixia-gong"       : return 2;
                case "shenghuo-shengong": return 2;
                case "longxiang-boruo"  : return 2;
                case "kurong-changong"  : return 1;
                case "linji-zhuang"     : return 1;
                  case "shenzhao-jing"     : return -1;
                case "shenyuan-gong"    : return -1;
                case "guiyuan-tunafa"   : return -2;
                case "dulong-dafa"      : return -2;
                case "huagong-dafa"     : return -2;
                case "hamagong"         : return -2;
                case "yunu-xinjing"     : return -3;
                case "hanbing-zhenqi"   : return -3;
                case "bihai-chaosheng"  : return -3;
                case "jiuyin-zhengong"  : return -4;
                default: return 1;
        }
}

int valid_learn(object me)
{
        int nlskill=me->query_skill("shenlong-yaoli",1);

        if(nlskill<(me->query_skill("dulong-dafa",1)-100)
         && me->query_skill("dulong-dafa",1 ) < 301)
           return notify_fail("�������ҩ��ѧ�����򻹲���");	

        if ((int)me->query_skill("dulong-dafa", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("dulong-dafa", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");
        return valid_public(me);
}

int practice_skill(object me)
{
       int lvl = me->query_skill("dulong-dafa",1);
       if(lvl >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("dulong-dafa", (int)me->query_int()*300/lvl+1);
		   //����а���������ص㣬��ʼ��Ѹ�٣�������������
		   //300���Ǹ��ֽ�㡣
		   //300����ʱ���ԭ����ƽ��
                   me->add("neili", -100*lvl/300); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ��������߶������ˡ�\n");   
       }
          return notify_fail("������ֻ����ѧ(learn)�����������������ȡ�\n");
}

string exert_function_file(string func)
{
    string * weapon;
    object me=this_player();
    int hua;
    
    hua=strsrch(func,"hua");
    weapon=explode(func,"hua");
    if(hua!=-1 && sizeof(weapon)>0)
    	me->set_temp("wea_type",weapon[0]);
    else if(me->query_temp("wea_type",1))
	me->delete_temp("wea_type");
    if(hua!=-1)
        return SKILL_D("dulong-dafa/hua");
    else
        return SKILL_D("dulong-dafa/") + func;
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : BLU + me->name()+"�����ڵ�����ϥ����������һ�ź��������š�" NOR,
    "start_my_msg" : "����ϥ���£�˫�ֺ�ʮ����ͷ����Ǳ��������һ�ź������������Χ��������˫��ð��һ˿�̹⡣\n",
    "start_other_msg" : me->name()+"��ϥ����������һ�ź��������ţ������̹����䣬���ɱ��ӡ�\n",
    "halt_msg" : "$N˫�ۻ����պϣ�Ƭ���͵������������̹⼱�������\n",
    "end_my_msg" : "��ֿ�˫�֣������������£����е��̹�Ҳ��������������\n",
    "end_other_msg" : me->name()+"�ֿ�˫�֣������������£����е��̹�Ҳ��������������\n"
  ]);
}
