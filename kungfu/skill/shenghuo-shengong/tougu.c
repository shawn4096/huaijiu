// tougu.c ͸����
// by snowman
// Modify By River@SJ ������9�����Ч�� 2000.2.22
#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int exert(object me, object target)
{        
        object weapon;
        int damage,p,force;
        string msg, *limbs;
        weapon = me->query_temp("weapon");

        if( !target) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("͸����ֻ����ս���жԶ���ʹ�á�\n");

        if(!weapon)
                return notify_fail("�����ʹ������������͸�����ھ���\n");        

        if( (int)me->query_skill("shenghuo-shengong",1) < 100 )
                return notify_fail("���ʥ���񹦵ȼ�����������ʩչ͸�����ھ���\n");

        if( (int)me->query_skill("force", 1) < 100 )
                return notify_fail("��Ļ����ڹ��ȼ�����������ʩչ͸�����ھ���\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("����������㣬����ʩչ͸�����ھ���\n");

        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("����������㣬����ʩչ͸�����ھ���\n");

        if( (int)me->query("jingli") < 300 )
                return notify_fail("��ľ������㣬����ʩչ͸�����ھ���\n");

        if( target->is_busy()) 
                 return notify_fail("�Է����Թ˲�Ͼ�أ��㲻æʩչ͸�����ھ���\n");

        me->start_exert(3, "͸����");  
        me->start_perform(3, "͸����");

        force = me->query_skill("force") + me->query_skill("jiuyang-shengong", 1)/10;
        tell_object(me,HIW"����������"HIB"͸����"HIW"����һ�ɼ�����������������һ�㣬��"+weapon->name()+"�ϴ�����ֱ��"+target->name()+"��\n"NOR);
        if(random(force) > target->query_skill("force")/2){
           damage = force;
           damage += random(damage);
           if(target->query_skill("force") - 50 > force)
             damage = damage/2;
           if(target->query_skill("force") > (force)*2)
              damage = random(10);
           if((force) > target->query_skill("force")*2)
              damage = damage+random(damage);
             if (damage > 1500) damage = 1500;
           if(damage > 300)
              tell_object(target, HIB"\nͻȻ֮�䣬���ؿ�һʹ���ƺ���һö��ϸ�ļ������һ�¡���һ�´�ʹ\n"+
                                     "ͻ�������������Σ�ʵ���ʣ�һ�ɺ���ͻ����Ļ����񹦣�ֱ�����ķΣ�\n"NOR);
              else if(damage <= 10){
                damage = 10;
                tell_object(target, HIY"\nͻȻ֮�䣬���ؿ�һʹ���ƺ���һö��ϸ�ļ������һ�¡��Һ��㻤���񹦱�\n"+
                                       "��ȫ������������������˿��֮ϸ��ٿ�궸�����ѷ��ѵ���ȴҲ���㲻�ã�\n"NOR);
                tell_object(me, HIY"�����ˡ�͸���롱���ھ��������Է����Ǻ��������ĵֵ���������\n"NOR);
              }
           else tell_object(target, HIB"\nͻȻ֮�䣬���ؿڱ��������һ�¡���ʹ�����Σ�ʵ���ʣ�һ�ɺ���ͻ�����\n"+
                                       "�����񹦣�ֱ�����࣡�������壬������ʧ������һ�̿ɵ�����ʹ��ǣ�\n"NOR);
           target->receive_damage("qi", damage, me);
           target->receive_wound("qi", damage/3, me);
           me->receive_damage("neili", damage/3);
           limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"ͻȻȫ��һ������ͬ���������һ�£�\n" NOR, ({ target }));  
           msg = damage_msg(damage, "����");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           message_vision(msg, me, target);
           me->start_busy(1);
           me->add("jingli", -20);
           target->start_busy(2+random(4));
           return 1;
        }        
        else {
           me->add("neili", -50);
           me->add("jingli", -5);
           tell_object(me, HIY"���͸�����ھ���û����"+target->name()+"���Ѿ�ɢ�ˡ�\n"NOR);
           me->start_busy(2);         
        }
        return 1;
}
