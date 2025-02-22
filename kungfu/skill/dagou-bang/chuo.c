// chuo.c 打狗棒法--戳字诀
// Creat by Looklove@SJ 2001.4.9
// Modified by Looklove@SJ 2001.5.19

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HBWHT"戳字诀"NOR; }
int perform(object me, object target)
{
        string msg;
        object tweapon, weapon;
        int mexp, texp, mlvl, tlvl, i, j, b, n;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「戳字诀」只能对战斗中的对手使用。\n");

        weapon = me->query_temp("weapon");
        if( !weapon
          || weapon->query("skill_type") != "stick"
          || me->query_skill_mapped("stick") != "dagou-bang" )
               return notify_fail("你现在无法使用「戳字诀」。\n");

        mexp=me->query("combat_exp");
        texp=target->query("combat_exp");

        mlvl=me->query_skill("dagou-bang",1);
        tlvl=target->query_skill("dodge",1);

        i = me->query_int();
        j = target->query_int();
        b = me->query_skill("bangjue",1);

        tweapon = target->query_temp("weapon");

        if(mlvl < 120 )
                return notify_fail("你的打狗棒法还不够娴熟，不会使用「戳字诀」。\n");

	if( b < 120 )
		return notify_fail("你的打狗棒诀不够娴熟，无法使出「戳字诀」。\n");

       	if((int)me->query_skill("huntian-qigong",1) < 120 )
       		return notify_fail("你的混天气功根基不足，无法使出「戳字诀」。\n");

        if((int)me->query("neili") < 600 )
               return notify_fail("你的内力不够。\n");

       	if((int)me->query("max_neili") < 2000)
             return notify_fail("你内力修为现在不够, 不能用「戳字诀」！\n");

       	if((int)target->query_condition("no_exert") > 10)
             return notify_fail("对方已经被你的戳字诀点中，大胆进攻吧！\n");

       	n = b /20 + random(b/50)+mlvl/50+random((i+j)/10);
       	if( mlvl > 350 ) n += (mlvl-350)/10;

	if(wizardp(me)) write(sprintf(HIR"n=%d \n"NOR,n));
	me->start_perform(2, "戳字诀");

	i = mexp/1000*mlvl*i;
	j = texp/1000*tlvl*j;

	msg = HBWHT"$N使出打狗棒「戳字诀」，"+weapon->name()+HBWHT"连环不断，连点带戳直向$n周身招呼！\n"NOR;

        if( random(i) > j/2 ){
                msg += HBWHT"$n身形闪了几闪，慌乱中一个措手不急，被"+weapon->name()+HBWHT"猛的戳中要穴。\n"NOR;
                msg += HBCYN"结果$n顿时面色苍白，感觉浑身内息大乱，头重脚轻。\n"NOR;
                target->start_busy(1+random(2));
                target->set_temp("dgb/chuo", n);
                target->apply_condition("no_force",n);
        }
        else {
                if (tweapon) msg += HBWHT"$n大吃一惊，连忙奋力用"+tweapon->name()+HBWHT"在"+weapon->name()+HBWHT"上一拨。\n"NOR;
                else msg += HBWHT "$n心中暗叫不好，用力提气纵身，跳后数步，避过了"+weapon->name()+HBWHT"的来势。\n" NOR;
		if (random(mexp)>texp/2){
                	msg += WHT "不料$N早已料到$n有此一招，手中"+weapon->name()+WHT"一转，改戳$n的脚踝。\n" NOR;
                	msg += WHT ""+weapon->name()+WHT"来势甚急，$n已经避无可避，扑通一身，应声而倒。\n" NOR;
                	target->apply_condition("no_exert",n*3/2);
                	target->start_busy(2+random(2));
                }
                me->start_busy(1+random(2));
        }
	message_vision(msg, me, target);
	me->add("neili",-200);
	return 1;
}

int help(object me)
{
	write(HBWHT"\n打狗棒「戳字诀」："NOR"\n");
	write(@HELP
	打狗棒招式异常灵活，可横扫竖打，此「戳字诀」便是连点
	带戳，招招不离对手内息相关之要穴，一旦戳中，将封住对
        手之内息脉路，一定时间内使对手内息大乱而不能自行调整。

	要求：	最大内力 2000 以上；
		当前内力 600 以上；
		打狗棒等级 120 以上；
		混天气功等级 120 以上；
		打狗棒诀等级 120 以上：
		激发招架为打狗棒。
HELP
	);
	return 1;
}