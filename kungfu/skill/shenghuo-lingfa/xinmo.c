// xinmo.c 圣火令法--心魔
// By River@SJ 
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill;
        object weapon;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target)
         || !living(target) )
             	return notify_fail("你只能在战斗中体验圣火令法的心魔威力。\n");

        if((int)me->query("neili") < 200 ) 
             	return notify_fail("你的内力不够。\n");

        if((int)me->query("jingli") < 200 ) 
             	return notify_fail("你的精力不够。\n");

        if((int)me->query_temp("ling")) 
             	return notify_fail("你已经在运功中了。\n");

        if(me->query_temp("shlf_ji"))
             	return notify_fail(target->name()+"已经被你的「击」字诀所迷惑，你可以放心的攻击了。\n");

        skill = (int)me->query_skill("shenghuo-lingfa", 1);
        if(skill < 120)
             	return notify_fail("你的圣火令法等级还不够。\n");

        if(me->query_skill("qiankun-danuoyi", 1) < 120)
             	return notify_fail("你的乾坤大挪移等级还不够。\n");

        if(me->query_skill("shenghuo-shengong", 1) < 120)
             	return notify_fail("你的圣火神功等级还不够。\n");

        if(!weapon=me->query_temp("weapon"))
             	return notify_fail("你不用兵器怎么提高你的圣火令法的心魔威力？\n");

        if ( me->query_skill_mapped("dagger") != "shenghuo-lingfa"
          || me->query_skill_mapped("parry") != "qiankun-danuoyi"
          || me->query_skill_mapped("cuff") != "shenghuo-lingfa"
          || me->query_skill_prepared("cuff") != "shenghuo-lingfa" 
          && userp(me))
             	return notify_fail("你必须先将圣火令法功和乾坤大挪移相互配合。\n");

        if(userp(me) && me->query("shen") < - 20000)
             	return notify_fail("你戾气太高了，提高圣火令法太过危险。\n");

        if(userp(me)){
           	me->add("jingli", -80);
           	me->add("neili", -150);
           	me->add("shen", - me->query_skill("shenghuo-lingfa",1)*5-random(1000));
        }
        message_vision(HIR"\n$N此刻乍逢劲敌，将圣火令法中的精微处尽数发挥出来，心灵渐受感应，突然间哈哈哈仰天三笑，\n"+
                          "声音中竟充满了邪恶奸诈之意。\n\n" NOR, me);

        skill += me->query_skill("jiuyang-shengong", 1)*4/7;
        skill = skill/2 + random(skill/2);
        me->add_temp("apply/attack", skill/5 );
        me->set_temp("ling",skill/5);
/*      if( me->is_fighting() && userp(me))
        	me->start_busy(2); */
        me->start_perform(2+random(2),"心魔");
        call_out("remove_effect", 1, me, weapon, skill/3);
        return 1;
}

void remove_effect(object me, object weapon, int count)
{
        if ( !me ) return;
        if (objectp(me) && me->query_temp("ling")) {
          	if (count-- > 0
		&& me->is_fighting()
		&& me->query_skill_mapped("cuff") == "shenghuo-lingfa"
		&& me->query_skill_prepared("cuff") == "shenghuo-lingfa"
		&& me->query_temp("weapon")
		&& weapon == me->query_temp("weapon")) {
              		call_out("remove_effect", 1, me, weapon, count);
              		return;
          	}
          	me->add_temp("apply/attack", - me->query_temp("ling"));
          	me->delete_temp("ling");
          	tell_object(me, HIW"\n你心魔慢慢消退，圣火令法立时不能连贯，威力大减。\n"NOR);
          	tell_room(environment(me), HIW+ me->name() + "心魔慢慢消退，圣火令法立时不能连贯，威力大减。\n", ({ me }));
        }
}
