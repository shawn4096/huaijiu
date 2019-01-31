// douzhuan-xingyi ��ת����
// 1997-2-14
#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";

string *parry_msg = ({
YEL"�����һ��������������$Nһ��һ����$N��������Խ����������һ��"NOR,
BLU"$N����һ����������$L��$n����$N��$L������Ī��������ﻬ��һ��"NOR,
HIW"$N˫��ǰ̽����۴���$n�ұۣ��ұ�ʹ��$n��������$n���л�ȥ"NOR,
HIY"$N���ƶ�ת��$n����Ī�����������;ת�˷���ֱ���Լ�Ϯ��"NOR,
YEL"$N�����Ϲۣ�˫����Է��ཻ���ƣ�̸Ц�侹ʹ��$n�������գ�ʹ��$n��֪����Ǻ�"NOR,
BLU"$N����������$n�͹����ʹ������������$n�ĳ�����������$n��������������"NOR,
HIW"ֻ��$N����Ʈ�磬ǡ���������ƣ������һʽ��˫�ƶ����޶�����׽��������$n��$l"NOR,
HIY"$N����Ʈ�������������ƶ�ת֮�䷴��$n����������$n��ȴ����$n��˼�������"NOR,
});

int valid_enable(string usage)
{
	return usage == "parry";
}

string query_parry_msg(object weapon)
{
	
		return parry_msg[random(sizeof(parry_msg))] + "��\n";
}

int valid_learn(object me)
{
     return notify_fail("��ת����ֻ��ͨ����������ߡ�\n");
}

int practice_skill(object me)
{
	return notify_fail("��ת����ֻ��ͨ����������ߣ��޷�ͨ����ϰ����ߡ�\n");
}

string perform_action_file(string action)
{
	return __DIR__"douzhuan-xingyi/" + action;
}

//modify from qiankun-danuoyi
int ob_hit(object ob, object me, int damage)
{
        string msg;
        int p,j,skill, neili, neili1, exp, exp1;
        skill = me->query_skill("douzhuan-xingyi", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");
        exp = me->query("combat_exp");
        exp1 = ob->query("combat_exp");

        if(!living(ob)) return damage;
        if(neili < 300) return damage;

	 if(me->query_temp("dzxy")){
           me->delete_temp("dzxy");
           return 1;
           }

      
        if(me->query("jiali") && random(skill)+20 > random(ob->query_skill("parry", 1)) 
         && exp > exp1/2 && skill > 50
         && neili > 300 && living(ob)){
    
   message_vision(GRN"$N��ʱ�Բ�������������������ͼ��$n�Ĺ���ת��$n�Լ����ϣ�\n"NOR,me, ob); 

       if(neili >= neili1+random(neili1)+damage){
            message_vision(HIY"���$n������$N����ͼ����ʽ���䣬$N��һ��ȴδ�ɹ���\n"NOR,me, ob);
            return damage;
            }else{ 
   message_vision(HIR"$nֻ���ƺ�˫�ֲ���ʹ������ʽ��$Nһ��һ����ֱ��$n�Լ�����������\n"NOR,me,ob);
         if(random(2)==1) me->add_temp("dzxy", 1); 
              ob->receive_damage("qi", damage);
              ob->receive_wound("qi", damage/10);
              p = ob->query("qi")*100/ob->query("max_qi");
              msg += damage_msg(damage, "����");
              msg += "( $n"+eff_status_msg(p)+" )\n";
              j = -(damage*2+skill);
              }
        }else{       
           msg = parry_msg[random(sizeof(parry_msg))];
             if(neili >= random(neili1)+damage){
              msg += "���������ж����$n��������\n";              
              j = -(damage+skill);
              }
           else{
              j = damage/2+random(damage/2); 
              if(j<damage/2) msg += "���ж����һЩ$n��������\n";
              else msg += "���ж����$nһ���������\n";
              j = -j;
              }
           }           
           message_vision(msg, me, ob);
           return j;
          
     
}
     