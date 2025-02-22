// Modify By River 99.5.26
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string *pictures=({
"心惊肉跳","杞人忧天","无中生有","拖泥带水","徘徊空谷","力不从心","行尸走肉", "庸人自扰"
});

int perform(object me)
{
        object target;
        string picture;
        int i,j;       
        i = me->query_skill("anran-zhang", 1)/2;
        if( me->query("eff_qi") > 0)
        j = me->query("max_qi") / me->query("eff_qi");
        else j = 0;
        picture = pictures[random(sizeof(pictures))];

        if( !target ) target = offensive_target(me);

        if( !target
         || !me->is_fighting(target) )
               return notify_fail("「销魂」只能在战斗中对对手使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「销魂」绝技！\n");   

        if( me->query_skill_prepared("strike") != "anran-zhang"
         || me->query_skill_mapped("strike") != "anran-zhang"
         || me->query_skill_mapped("parry") != "anran-zhang"
         || me->query_skill_mapped("force") != "yunu-xinjing")
               return notify_fail("你现在难以使用「销魂」绝技！\n"); 

        if((int)me->query_skill("anran-zhang", 1) < 150 )
               return notify_fail("你的黯然销魂掌法火候不够，使不出「销魂」绝技。\n");

        if((int)me->query_skill("strike", 1) < 150 )
               return notify_fail("你的基本功还不够娴熟，使不出「销魂」绝技。\n");

        if((int)me->query_skill("force") < 200 )
               return notify_fail("你的内功等级不够，使不出「销魂」绝技。\n");

        if((int)me->query_temp("xinjing")) 
                return notify_fail("你正在使用「心经」字诀。\n");

        if((int)me->query_str() < 30)
               return notify_fail("你的膂力还不够强劲，使不出「销魂」绝技。\n");

        if((int)me->query_dex() < 30)
                return notify_fail("你的身法还不够迅猛，使不出「销魂」绝技。\n");

        if((int)me->query_skill("yunu-xinjing", 1) < 150 )   
                return notify_fail("你的玉女心经修为不够，无法使用「消魂」绝技。\n");  

        if((int)me->query_temp("xiaohun")) 
                return notify_fail("你现在正在使用「消魂」绝技。\n"); 

        if((int)me->query("max_qi") <= (int)me->query("eff_qi"))
                return notify_fail("以你现在的心境难以使用发挥出消魂绝技。\n"); 

        if((int)me->query("neili") < i*3 )
                return notify_fail("你的内力不够。\n");

        if((int)me->query("jingli") < i*2)
                return notify_fail("你的精力不够。\n");

        message_vision(HIW"\n$N心想今日身陷绝境，不由万念俱灰，凄然之意自心而升，没精打采的拍出一掌「"+picture+"」，\n"+
                          "但见掌风激荡，恍恍惚惚，隐隐约约！刹时黯然销魂掌威力顿增，势不可挡。\n"NOR,me,target);

        j *= i;
        if ( j > 350 ) j = 350;

        me->add("neili", -i*2);
        me->add("jingli", -i/2);
        me->add_temp("apply/attack", j);
        me->start_perform(2,"消魂绝技");
        me->set_temp("xiaohun", j );
        call_out("check_fight", 1 , me, target);
        return 1;
}

void check_fight(object me,object target)
{
        int time;
        if (!me) return;
        time = me->query_skill("force")/5; 
        if (me->query_temp("weapon")
         || me->query_temp("secondary_weapon")
         || me->query_skill_prepared("strike") != "anran-zhang" ){
            me->add_temp("apply/attack", - me->query_temp("xiaohun"));
            me->delete_temp("xiaohun");
            tell_object(me, HIR"\n你「消魂」绝技运行完毕，气回丹田.\n" NOR);
            return;
        }
        if ( ! target
         || time < 1
         || ! me->is_fighting(target)) {
            me->add_temp("apply/attack", - me->query_temp("xiaohun"));
            me->delete_temp("xiaohun");
            tell_object(me, HIR"\n你「消魂」绝技运行完毕，气回丹田.\n" NOR);
            return;
        }
        call_out("check_fight", 1, me, target,time -1);
}
