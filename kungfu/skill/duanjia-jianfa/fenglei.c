//风雷 fenglei.c 

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int i,a;

        weapon = me->query_temp("weapon");
       
        if( !target ) target = offensive_target(me);
        if (!target) return notify_fail("你要对谁攻击？\n");

        if( !me->is_fighting() )
                return notify_fail("「风雷四击」只能在战斗中使用。\n");
 
        weapon = me->query_temp("weapon");
        if (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "duanjia-jianfa")
                return notify_fail("手中无剑,你怎么使得出「风雷四击」！\n");

        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力不够！\n");
                
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够！\n");

        if( (int)me->query("jingli") < 300 )
                return notify_fail("你的精力不够！\n");

        if( (int)me->query_str() < 24 )
                return notify_fail("你的臂力不够！\n");

        if( (int)me->query_dex() < 24 )
                return notify_fail("你的身法不够！\n");

        if(!me->query_skill("kurong-changong", 1))
          if(me->query_skill("qiantian-yiyang", 1) < 100)
                return notify_fail("以你现在的内功修为还使不出「阳关三叠」。\n");        
         
        if (me->query_skill_mapped("force") != "kurong-changong" )
          if(me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("你所使用的内功不对。\n");

        if( (int)me->query_skill("duanjia-jianfa",1) < 100 )
                return notify_fail("你的段家剑法还不到家，无法使用「风雷四击」绝技！\n");

        if( (int)me->query_skill("sword",1) < 100 )
                return notify_fail("你的剑法造诣不够，无法使用如此高深的「风雷四击」绝技！\n");

        if( (int)me->query_skill("qingyan-zhang",1) < 100 ||
            me->query_skill_mapped("strike") != "qingyan-zhang")
                return notify_fail("你的五罗清烟掌还不到家，无法使用「风雷四击」绝技！\n");

        if( (int)me->query_skill("strike",1) < 100 )
                return notify_fail("你的掌法造诣不够，无法使用如此高深的「风雷四击」绝技！\n");

        if (me->query_skill_prepared("strike") != "qingyan-zhang"
          || me->query_skill_mapped("parry") != "qingyan-zhang")
                return notify_fail("你现在无法使用「风雷四击」进行攻击。\n");

        if( (int)me->query_skill("tianlong-xiang",1) < 100 )
                return notify_fail("你的天龙降还不到家，无法使用「风雷四击」绝技！\n");


        i = ((int)me->query_skill("duanjia-jianfa",1)+(int)me->query_skill("qingyan-zhang",1))/8;
        message_vision(BLU"\n$N蹂身而上，左手五罗清烟掌，右手段家剑，施展一绝招「风雷四击」！$n \n"NOR, me,target);
        me->add("neili",-(150+random(50))); 
        if (i < 100) i=100;
        me->add("jingli",-50); 
		me->set_temp("fenglei",4);
        for(a=0;a<4;a++)
        {
		     if(random(2)) me->set_temp("fl_sword",1);

		     if (me->query_temp("fl_sword"))
		   {
		         me->add_temp("apply/attack", i);
                         me->add_temp("apply/sword", i);
		         if(me->is_fighting(target))
		         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); 
                         me->add_temp("apply/sword", -i);
                         me->add_temp("apply/attack", -i);
                } else {
		         weapon->unequip();
        		 me->add_temp("apply/attack", i);
                         me->add_temp("apply/strike", i);
                         if(me->is_fighting(target))
		         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); 
                         me->add_temp("apply/attack", -i);
                         me->add_temp("apply/strike", -i);
                         weapon->wield();
           }
     me->delete_temp("fl_sword");
        }
		me->delete_temp("fenglei");
		me->delete_temp("fl_sword");
        me->start_perform( 3 + random(2), "「风雷四击」");
        me->start_busy(2);
        return 1;
}
