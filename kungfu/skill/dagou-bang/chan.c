// chan.c 打狗棒法--缠字诀
// Modify by looklove@SJ 3/16/2001

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HBGRN"缠字诀"NOR; }
int perform(object me, object target)
{
        string msg;
        object tweapon, weapon;
        int busy, mexp, texp, mlvl, tlvl, x, y, b;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("［缠字诀］只能对战斗中的对手使用。\n");

        weapon = me->query_temp("weapon");
        if( !weapon
          || weapon->query("skill_type") != "stick"
          || me->query_skill_mapped("stick") != "dagou-bang" )
               return notify_fail("你现在无法使用缠字诀。\n");

        mexp=me->query("combat_exp");
        texp=target->query("combat_exp");

        mlvl=me->query_skill("dagou-bang",1);
        tlvl=target->query_skill("dodge",1);

        x = me->query_int();
        y = target->query_int();
        b = me->query_skill("bangjue",1);

        tweapon = target->query_temp("weapon");

        if(mlvl < 100 )
                return notify_fail("你的打狗棒法还不够娴熟，不会使用缠字诀。\n");

	if( b < 100 )
		return notify_fail("你的打狗棒诀不够娴熟，无法使出缠字诀。\n");

       	if((int) me->query_skill("huntian-qigong",1) < 100 )
       		return notify_fail("你的混天气功根基不足，无法使出缠字诀。\n");

        if((int)me->query("neili") < 500 )
               return notify_fail("你的内力不够了。\n");

	if((int)me->query("jingli") < 100 )
		return notify_fail("你的精力不足以让你使出此绝技。\n");

        if((int)me->query("max_neili") < 1000 )
               return notify_fail("你的内力不够支持你使用此绝技。\n");

        if( target->is_busy()||target->query_temp("dgb/chan"))
               return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

       	if ( x>y ){
       		busy = 2+(x-y)/2 + random(x-y);
       		busy += random(b/40);
       	}
       	else 	busy = 1+(y-x)/5;
       		busy += random(b/50);

       	if( mexp > texp ) busy += mexp/(texp+1);
       	if( busy > 6) busy = 6;
       	if( mlvl > 350 ) busy += (mlvl-350)/50;

	me->start_perform(3+random(2), "缠字诀");

        if(wizardp(me)||me->query("id")=="looklove") write(sprintf(HIR"busy=%d\n"NOR,busy));
	x = mexp/1000*mlvl*x;
	y = texp/1000*tlvl*y;

	msg = HBGRN"$N信手使出「缠字诀」，手中"+weapon->name()+HBGRN"舞成一团棒影，直往$n罩了过去。\n"NOR;
	if( tweapon )
       	msg += HBGRN"只见$n的"+tweapon->name()+HBGRN"挥到东，"+weapon->name()+HBGRN"就跟向东，"+tweapon->name()+HBGRN"打到西，"+weapon->name()+HBGRN"随到西。\n"NOR;
       	else
       	msg += HBGRN"只见"+weapon->name()+HBGRN"如影随形，招招不离$n周身大穴，当真精妙无比。\n"NOR;

        if( random(x) > y/3 ){
                msg += HIM "$n左蹿右跳，始终逃不出棒影，无论闪向哪里，都有"+weapon->name()+HIM"随后跟到。\n" NOR;
                target->start_busy(busy);
                target->set_temp("dgb/chan", 1);
                call_out("check_fight", 1, me, target, weapon, busy);
        }
        else if( random(x+y) > y ){
                msg += HIM "结果$n顿时手忙脚乱，施展出浑身解数，也脱不开$N的棒影。\n" NOR;
                target->start_busy(busy);
                target->set_temp("dgb/chan", 1);
                call_out("check_fight", 1, me, target, weapon, busy);
        }
        else if( random(y) > x/2 ){
                msg += HIW "$n见势不好，大喝一声：“我打！”$N不由心神激荡，棒影随后落空。\n" NOR;
                me->start_busy(1+random(2));
        }
        else {
                msg += HIW "$n镇定自若，寻个破绽，信手在"+weapon->name()+HIW"上一点，漫天棒影顿时消失了。\n" NOR;
                me->start_busy(1+random(2));
        }
       	me->add("neili", -200);
        me->add("jingli", -60);
	message_vision(msg, me, target);
	return 1;
}

void check_fight(object me,object target,object weapon,int busy)
{
        int ap, dp, cost;
       
       	cost = me->query_skill("dagou-bang", 1)/2;
       	ap = me->query("combat_exp")/1000 * me->query_skill("dagou-bang",1) * me->query_int();
       	dp = target->query("combat_exp")/1000 * target->query_skill("dodge",1) * target->query_int();
       	if (ap < 1) ap = 1;
       	if (dp < 1) dp = 1;

       	if( !target) return;
       	if( !target->query_temp("dgb/chan")) return;
       	if( ! me
         || ! me->is_fighting(target)
         || weapon != me->query_temp("weapon")
         || me->query_skill_mapped("stick") != "dagou-bang"
         || (int)me->query("neili") < 500 
         || random(ap + dp) < dp
         || busy < 1){
           	target->delete_temp("dgb/chan", 1);
		target->add_busy(1);
           	return;

       }
	me->start_perform(1+random(2), "缠字诀");
       	me->add("neili", -cost);
       	me->add("jingli", -10);
       call_out("check_fight", 1, me,target,weapon,busy -1);
}

int help(object me)
{
	write(HBGRN"\n打狗棒「缠字诀」："NOR"\n");
	write(@HELP
	昔年洪七公以打狗棒之轻灵奇巧，跻身当世五大高手。
	这打狗棒「缠字诀」，正是洪七公当年惯使的一招成名绝技。
	那施展出浑身解数，也脱不开的如梦幻般的棒影，令对手心惊肉跳。

	要求：	最大内力 1000 以上；
		当前内力 500 以上；
		打狗棒等级 100 以上；
		混天气功等级 100 以上；
		打狗棒诀等级 100 以上：
		激发招架为打狗棒。
HELP
	);
	return 1;
}
