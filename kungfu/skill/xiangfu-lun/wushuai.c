// xiangfu-lun perform
// by iceland
// changed by emnil     2/7/2000
// re-write by snowman@SJ 28/11/2000
// Modified by snowman@SJ 05/07/2001. �������У��������


#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

#define THROW_CMD       "/cmds/std/throw"

string  *throw_msg = ({
HIY"$N���ִ��ڷ�������б��һ���������ڿ��л���һ�����ߣ���$n��ȥ��������ţ��\n"NOR,
HIY"$N����������أ�����ǰ���һ��һ�ͣ����ֶ�Ȼ���𣬴Ӳ���˼��ĽǶ�ײ��$n\n"NOR,
HIY"$N����������˫�����ƣ�����ȥ�ƾ������ص�һ������$n��\n"NOR,
HIY"$N˫�ֻ��ţ�����$n��ǰ�������ڿ�����ת���أ�Ϯ��$n�ĺ��ԡ�\n"NOR,
HIY"$N������һ���Ϻȣ�����ȭӲ�������ڷ����ϣ����ַ����͵�һת��ֱ׷��$n��\n"NOR,
HIY"$N����Ȧת���������������ɽ������У����������󼱷�������ƽ�ƣ���������$n��$l��\n"NOR,
HIY"$Nƾ���������ֶ����������ϼ������۹�ɨ��$n�����ֽ����ŷ��˹�ȥ��\n"NOR,
HIY"$NԾ���գ�˫�����϶����Ƴ�������ƾ�ռ��٣����ƾ��ˡ�\n"NOR,
HIY"$N��ǰ����������һת�������ͳ����֣������$n���ļ��ƣ���ס��$n����·��\n"NOR,
});
string  *dodge_msg = ({
HIC"$n��������ת�漲������ֻ�����絶������æһ���Ծ�𣬷��ֺ��Ĵӽ��·ɹ���\n\n"NOR,
HIC"$n���Ų�æ�������ݰ㼱ת�˸�Ȧ�����˿�����\n\n"NOR,
HIC"$n���ֲ�����Σ����������ͷ�����ָպô�ͷ���ɹ���\n\n"NOR,
HIC"$nһ���෭�������ڿ��к����ȥ���ܹ���������һ����\n\n"NOR,
HIC"$n�������֮�⣬����֮��ֻ�ù����ڵأ���Щδ�ܱܹ���\n\n"NOR,
HIC"$n��׼���ƣ�˫��һ��һ�֣������ֵ��˿�ȥ��\n\n"NOR,
HIC"$n���˼�����š��һ�������������˿�ȥ��\n\n"NOR,
HIC"$n˫�������������ģ����ֱ�����ʧ��׼ͷ����$n���Է��˹�ȥ��\n\n"NOR,
});

int perform(object me, object target)
{
	string msg;
	int t, x, i, damage;
	object weapon;

	if( !target ) target = offensive_target(me);

	if( !target
	|| !target->is_character()
	|| !me->is_fighting(target) 
	|| !living(target))
		return notify_fail("��������˥��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	weapon = me->query_temp("weapon");
	if( !weapon || weapon->query("skill_type") != "hammer" )  
		return notify_fail("�������ʹ�÷���ʱ����ʩչ��������˥����\n");
	t = weapon->query_amount();
	if( t < 1 ) t = 1;
	
	if( me->query_skill_mapped("hammer") != "xiangfu-lun" )
		return notify_fail("����뼤�������ַ�����ʩչ��������˥����\n");
	x = me->query_skill("xiangfu-lun", 1);
	if( x < 150 )
		return notify_fail("��Ľ����ַ���������죬ʹ������������˥��������\n");

	if(me->query_skill("longxiang-boruo", 1) < 160 )
		return notify_fail("��������������δ�ﵽ�ڰ˲㾳�磬�޷�ʹ����������˥��������\n");

	if((int)me->query_skill("force") < 160 )
		return notify_fail("����ڹ��ȼ�������ʹ������������˥��������\n");

	if(me->query_skill_mapped("force") != "longxiang-boruo")
		return notify_fail("û�������������Ϊ���������޷�ʹ����������˥�������ģ�\n"); 

	if((int)me->query_str() < 40)
		return notify_fail("�������������ǿ����ʹ������������˥��������\n");
       
	if(me->query_skill_mapped("parry") != "xiangfu-lun")
		return notify_fail("��������˥����Ҫʹ�ý����ַ��м�һ�ез�������\n");		       

	if(me->query_skill_mapped("hammer") != "xiangfu-lun")
		return notify_fail("��������˥����Ҫʹ�ý����ַ������з���\n");		       

	if((int)me->query("max_neili") < 3000 )
		return notify_fail("��������Ϊ��ǳ��ʹ������������˥����\n");      

	if( (int)me->query("neili") < 600 )
		return notify_fail("����������̫����ʹ������������˥����\n");
	if( weapon->query("id") == "fenghuo lun" )
		t = 5;
	if( (int)weapon->query("hammer_count") )
		t = (int)weapon->query("hammer_count");
		
	msg = HIY"\nֻ������-��-��֮��������$N�����з�����ת������ʹ����������˥������������������\n"NOR;
	
	damage = me->query("str") /3;
	
	if( me->query_temp("xs/longxiang") ) {
		msg += MAG"$N���������ھ����ڱ���֮�ϣ�"+weapon->query("name")+MAG"ͨ����������������ɫ��â��\n\n"NOR;
		damage += 3;
	}
	message_vision(msg, me, target);

	me->start_perform(5,"������˥");
	me->start_busy(1);
	
	if( t > 5 ) t = 5;
	x /= 8;
	x += random(x);
	
	me->add_temp("apply/strength", x);
	weapon->unequip();
	i = 0;
	while(t--) {
		if(!objectp(target))    break;
		if( environment(target) != environment(me) || !me->is_fighting(target) ) break;

		weapon->set("throw/msg", throw_msg[i]);
		weapon->set("throw/dodge_msg", dodge_msg[i]);
		weapon->set("throw/damage", damage/3+random(damage));
		weapon->set("throw/catch_msg", "");
		weapon->set("throw/hit_msg", "���ֻ�������𡹵�һ�����죬$N��һ�����ݰ㱻���ɳ�ȥ��\n");
		THROW_CMD->do_throw(me, weapon, target);
		i++;
		me->add("neili", -(50+random(50)));
		if( me->query("neili") < 0 ){ 
			me->set("neili",0);
			message_vision(HIY"\n$N�������ӣ�һ�¿��Ʋ�ס��$n�����˵��ϣ�\n"NOR, me, weapon);
			weapon->move(environment(me));
			weapon->delete("throw");
			me->add_temp("apply/strength", -x);
			return 1;
			break;
		}
		else weapon->move(me);
	}
	weapon->wield();
	weapon->delete("throw");
	message_vision(HIY"\n$Ņ�ֽ�ס���µķ��֣�������������������һ�㣬�ж���������ࡣ\n"NOR, me);
	me->add_temp("apply/strength", -x);
	me->start_busy(-1);
	me->interrupt_me();
	me->start_busy(1);
	return 1;
}
