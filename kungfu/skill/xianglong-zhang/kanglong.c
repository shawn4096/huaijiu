// �����л�
// by snowman@SJ 16/10/99

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int kanglong_attack(object me);
int perform(object me)
{
        if( !me->is_fighting())
                return notify_fail("�������лڡ�ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á������лڡ���\n");

        if( (int)me->query_skill("xianglong-zhang", 1) < 200 )
                return notify_fail("��Ľ���ʮ���ƻ�������죬ʹ�����������лڡ�������\n");
  
        if( (int)me->query_skill("huntian-qigong", 1) < 180 )
                return notify_fail("��Ļ��������ȼ���������ʹ�����������лڡ�������\n");
  
if(me->query_temp("htqg/powerup"))
return notify_fail("������ʹ�û���������\n");
        if (me->query_skill_mapped("force") != "huntian-qigong")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");
  
        if( (int)me->query_skill("force") < 270 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á������лڡ���\n");

        if( (int)me->query_str() < 40 )
                return notify_fail("�������������ǿ����ʹ�����������лڡ�����\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang"
         || me->query_skill_mapped("strike") != "xianglong-zhang"
         || me->query_skill_mapped("parry") != "xianglong-zhang")
                return notify_fail("�������޷�ʹ�á������лڡ���\n");                                                                                 

        if((int)me->query("max_neili") < 4000)
                return notify_fail("����������̫����ʹ�����������лڡ���\n");      

        if((int)me->query("neili") < 1500 )
                return notify_fail("����������̫����ʹ�����������лڡ���\n");

        if((int)me->query_temp("xlz/xiao") ) 
                return notify_fail("���Ѿ���ʼ�˽���Х��\n");

        if(!me->query("xlz/hang"))
                return notify_fail("����ѧ�ĵ�һ�о��ǡ������лڡ������ǽ�������������С��һ�С�\n");
                
        tell_object(me, HIC"\n�㻺����˫���ᵽ��ǰ����Ϣ������������ת��Խ��Խ�죬������ȴ�������κζ���...\n\n"NOR);

        me->start_busy(1+random(2));
        me->start_perform(10, "�������лڡ�");
        me->start_call_out( (: call_other, __FILE__, "kanglong_attack", me :), 2+random(4));
        return 1;
}

int kanglong_attack(object me)
{
        object target;
        int i;
        
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !living(target)
         || !me->is_fighting(target) 
         || environment(target)!=environment(me)){
                write("�������лڡ�ֻ����ս���жԶ���ʹ�á�\n");
                return 0;
        }
        
        if( (int)me->query("neili") < 1500 ){
                write("����������̫����ʹ�����������лڡ���\n");
                return 0;
        }
        if( (int)me->query("jingli") < 1000 ){
                write("�����ھ���̫����ʹ�����������лڡ���\n");
                return 0;
        }

        if (me->query_skill_mapped("force") != "huntian-qigong"){
                write("����ʹ�õ��ڹ����ԡ�\n");
                return 0;
        }
        
        if (me->query_skill_prepared("strike") != "xianglong-zhang"
         || me->query_skill_mapped("strike") != "xianglong-zhang"
         || me->query_skill_mapped("parry") != "xianglong-zhang"
         || me->query_temp("weapon")){
                write("�������޷�ʹ�á������лڡ���\n");                                                                                 
                return 0;
        }

        if((int)me->query_temp("xlz/xiao") ) 
                return notify_fail("���Ѿ���ʼ�˽���Х��\n");
       
       i = me->query_skill("xianglong-zhang", 1)*4/10;
        
if(me->query_temp("bishen_target"))
target->set_temp("xlz/hanglong",1);
else
        me->set_temp("xlz/hanglong", 1);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/strength", i);
        me->add_temp("apply/damage", i/2);
        me->add_temp("apply/strike", i/2);
        
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
         
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/strength", -i);
        me->add_temp("apply/damage", -i/2);
        me->add_temp("apply/strike", -i/2);
        
        me->receive_damage("neili", 1400);
        me->receive_damage("jingli", 200);
        me->start_perform(4,"�������лڡ�");
        return 1;
}
