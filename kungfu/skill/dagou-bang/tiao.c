// tiao.c 打狗棒法--挑字诀
// Creat by looklove@SJ 3/17/2001

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HBMAG"挑字诀"NOR; }
int perform(object me, object target)
{
        string msg;
        object tweapon, weapon;
        int busy, mexp, texp, mlvl, tlvl, i, j, b;

        me->clean_up_enemy();
        target = me->select_opponent();
        
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("［挑字诀］只能对战斗中的对手使用。\n");

        weapon = me->query_temp("weapon");
        tweapon = target->query_temp("weapon");
        
        if( !weapon 
          || weapon->query("skill_type") != "stick"
          || me->query_skill_mapped("stick") != "dagou-bang" ) 
               return notify_fail("你现在无法使用挑字诀。\n");

        if (!tweapon)
                return notify_fail("对方没有使用任何兵器，你无法使用「挑字诀」。\n");

        mexp=me->query("combat_exp");
        texp=target->query("combat_exp");
        if( texp < 100 ) texp = 100;
        
        mlvl=me->query_skill("dagou-bang",1);
        tlvl=target->query_skill("dodge",1);
        
        i = me->query_int();
        j = target->query_int();
        b = me->query_skill("bangjue",1);
        
        if(mlvl < 160 )
                return notify_fail("你的打狗棒法还不够娴熟，不会使用挑字诀。\n");
	
	if( b < 160 ) 
		return notify_fail("你的打狗棒诀不够娴熟，无法使出挑字诀。\n");
        
       	if((int)me->query_skill("huntian-qigong",1) < 160 )
       		return notify_fail("你的混天气功根基不足，无法使出拌字诀。\n");

        if((int) me->query("neili") < 800 )
               return notify_fail("你的内力不够。\n");
       	
       	busy = random( b/50 );
       	if ( busy < 0 ) busy = 1 ;
       	if( mlvl > 350 ) busy = busy + (mlvl-350)/5;
	if (busy >4) busy = 4;
        
        if(wizardp(me)) write(sprintf(HIR"busy=%d \n"NOR,busy));
	
        msg = HBMAG"$N捏个棒诀将"+weapon->name()+HBMAG"一转，轻喝一声“起！”，使出「挑字诀」，搭住"+tweapon->name()+HBMAG"向上挑出。\n"NOR;
        me->start_perform(2,"挑字诀");

        mexp = mexp/1000*mlvl*i;
        texp = texp/1000*tlvl*j;
        
        if( random(mexp) > texp/4)
        {
		msg += HBMAG"$n只感"+tweapon->name()+HBMAG"似欲脱手飞出，一个把握不住，手中兵器被挑飞了出去。\n"NOR;
		target->start_busy(busy);
		me->add("neili",-300);
			
		if (random(2)!=1){
			msg += HIY"$N提气纵身，跃起丈余，将半空中的"+tweapon->name()+HIY"抢在手中。\n"NOR;
                	tweapon->move(me);
		}
		else {
			msg += HBMAG"$n眼望下落的"+tweapon->name()+HBMAG"伸手欲接，被$N"+weapon->name()+HBMAG"又一番疾攻。只好任"+tweapon->name()+HBMAG"落在一边。\n"NOR;
                	tweapon->move(environment(me));
		}
        }
        else
        {
                me->add("neili",-300);
                msg += HIG"$n运力于腕，斜下里一荡，将"+weapon->name()+HIG"从自己的"+tweapon->name()+HIG"上荡了开去。\n"NOR;
        }
        message_vision(msg, me, target);
        return 1;
}

int help(object me)
{
	write(HBMAG"\n打狗棒「挑字诀」："NOR"\n");
	write(@HELP
	打狗棒法集轻灵奇巧于一身，临敌之际纵不得伤敌，亦得自保。
	若对手手持兵器，则使用此「挑字诀」，可将对手兵器打飞或
	者挑入自己手中。
	
	要求：	当前内力 800 以上；
		打狗棒等级 160 以上；
		混天气功等级 160 以上；
		打狗棒诀等级 160 以上：
		激发招架为打狗棒；
		对手若手无兵器，则无效果。
HELP
	);
	return 1;
}