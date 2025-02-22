// xiangfu-lun perform
// by iceland
// changed by emnil     2/7/2000
// re-write by snowman@SJ 28/11/2000
// Modified by snowman@SJ 05/07/2001. 降低命中，提高威力


#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

#define THROW_CMD       "/cmds/std/throw"

string  *throw_msg = ({
HIY"$N伸手搭在法轮上往斜里一拨，法轮在空中划出一道弧线，向$n飞去，势如猛牛！\n"NOR,
HIY"$N不待法轮落地，抢上前伸脚一挑一送，法轮陡然飞起，从不可思议的角度撞向$n\n"NOR,
HIY"$N吐气发力，双掌齐推，法轮去势劲急，呜的一声冲向$n。\n"NOR,
HIY"$N双手箕张，拦在$n身前，法轮在空中旋转而回，袭向$n的后脑。\n"NOR,
HIY"$N霹雳般一声断喝，侧身单拳硬生生击在法轮上，法轮方向猛的一转，直追向$n。\n"NOR,
HIY"$N右手圈转，将法轮轻轻巧巧接在手中，紧接着手腕急翻，左手平推，法轮旋向$n的$l。\n"NOR,
HIY"$N凭内力将法轮定在手掌心上急旋，眼光扫向$n，法轮紧跟着飞了过去。\n"NOR,
HIY"$N跃入半空，双掌自上而下推出，法轮凭空加速，威势惊人。\n"NOR,
HIY"$N抢前几步，手腕一转，借势送出法轮，随后向$n虚拍几掌，封住了$n的退路。\n"NOR,
});
string  *dodge_msg = ({
HIC"$n见法轮旋转奇疾，锋利只怕犹如刀剑，连忙一个筋斗跃起，法轮呼的从脚下飞过。\n\n"NOR,
HIC"$n不慌不忙，如陀螺般急转了个圈，避了开来。\n\n"NOR,
HIC"$n措手不及，危急中弯腰缩头，法轮刚好从头顶飞过。\n\n"NOR,
HIC"$n一个侧翻，身体在空中横滚出去，避过了这雷霆一击。\n\n"NOR,
HIC"$n大出意料之外，无奈之下只得滚倒在地，险些未能避过。\n\n"NOR,
HIC"$n看准来势，双手一兜一分，将法轮荡了开去。\n\n"NOR,
HIC"$n倒退几步，拧腰一闪，将法轮让了开去。\n\n"NOR,
HIC"$n双掌运足内力疾拍，法轮被荡得失了准头，从$n身旁飞了过去。\n\n"NOR,
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
		return notify_fail("「天人五衰」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");
	if( !weapon || weapon->query("skill_type") != "hammer" )  
		return notify_fail("你必须在使用法轮时才能施展「天人五衰」！\n");
	t = weapon->query_amount();
	if( t < 1 ) t = 1;
	
	if( me->query_skill_mapped("hammer") != "xiangfu-lun" )
		return notify_fail("你必须激发降伏轮法才能施展「天人五衰」！\n");
	x = me->query_skill("xiangfu-lun", 1);
	if( x < 150 )
		return notify_fail("你的降伏轮法还不够娴熟，使不出「天人五衰」绝技。\n");

	if(me->query_skill("longxiang-boruo", 1) < 160 )
		return notify_fail("你的龙象般若功尚未达到第八层境界，无法使出「天人五衰」绝技。\n");

	if((int)me->query_skill("force") < 160 )
		return notify_fail("你的内功等级不够，使不出「天人五衰」绝技。\n");

	if(me->query_skill_mapped("force") != "longxiang-boruo")
		return notify_fail("没有龙象般若功作为根基，是无法使出「天人五衰」绝技的！\n"); 

	if((int)me->query_str() < 40)
		return notify_fail("你的膂力还不够强劲，使不出「天人五衰」绝技。\n");
       
	if(me->query_skill_mapped("parry") != "xiangfu-lun")
		return notify_fail("「天人五衰」需要使用降伏轮法招架一切敌方攻击。\n");		       

	if(me->query_skill_mapped("hammer") != "xiangfu-lun")
		return notify_fail("「天人五衰」需要使用降伏轮法攻击敌方。\n");		       

	if((int)me->query("max_neili") < 3000 )
		return notify_fail("你内力修为尚浅，使不出「天人五衰」。\n");      

	if( (int)me->query("neili") < 600 )
		return notify_fail("你现在真气太弱，使不出「天人五衰」。\n");
	if( weapon->query("id") == "fenghuo lun" )
		t = 5;
	if( (int)weapon->query("hammer_count") )
		t = (int)weapon->query("hammer_count");
		
	msg = HIY"\n只听“呜-呜-”之声大作，$N将手中法轮旋转掷出，使出「天人五衰」绝技，奋力掷出！\n"NOR;
	
	damage = me->query("str") /3;
	
	if( me->query_temp("xs/longxiang") ) {
		msg += MAG"$N更把龙象内劲附于兵刃之上，"+weapon->query("name")+MAG"通体流淌着异样的紫色光芒！\n\n"NOR;
		damage += 3;
	}
	message_vision(msg, me, target);

	me->start_perform(5,"天人五衰");
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
		weapon->set("throw/hit_msg", "结果只听见「硼」地一声巨响，$N像一捆稻草般被击飞出去！\n");
		THROW_CMD->do_throw(me, weapon, target);
		i++;
		me->add("neili", -(50+random(50)));
		if( me->query("neili") < 0 ){ 
			me->set("neili",0);
			message_vision(HIY"\n$N力气不接，一下控制不住，$n掉在了地上！\n"NOR, me, weapon);
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
	message_vision(HIY"\n$N抬手接住落下的法轮，气喘吁吁，犹如脱力一般，行动迟滞了许多。\n"NOR, me);
	me->add_temp("apply/strength", -x);
	me->start_busy(-1);
	me->interrupt_me();
	me->start_busy(1);
	return 1;
}
