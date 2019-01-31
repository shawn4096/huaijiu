// riyun.c
// by snowman@SJ 27/01/2000

#include <ansi.h>
int check_fight(object me, int nh);

void remove_effect(object me, int nh);

int exert(object me)
{       
        int nh, neili;
       
        if( !me->is_fighting() )
             return notify_fail("「日月」字决必须在战斗中使用。\n");

        if((int)me->query_skill("linji-zhuang", 1) < 150)
             return notify_fail("你的临济十二庄修为还不够。\n");

        if( me->query("class") != "bonze" && me->query("family/generation") > 3)
            return notify_fail("你不是出家人，无法领会临济十二庄的「日月」字决！\n");

        if((int)me->query("neili") < 1000 )
             return notify_fail("你的真气不够。\n");
        
        if( me->query_temp("ljz/riyue"))
             return notify_fail("你正在运用临济十二庄的「日月」字决！\n");

        tell_object(me,MAG"\n你五心向天，潜运日月二庄，益气升阳，益阴潜阳，升降反正，天地二气交泰于身，顿觉自己内力源源不止了。\n"NOR);
        message_vision(HIW"\n只见$N脸上红光时隐时现，一下变得神采弈弈。\n\n"NOR, me);

        nh = (int)me->query_skill("linji-zhuang", 1)/10;

        if( me->query("emjiuyin")) {
             tell_object(me,HIB"\n你将九阴总决融合于临济十二庄之中,功夫威力陡然大增！。\n"NOR);
             message_vision(HIB"\n只见$N使出九阴「玄阴诀」，迅捷无比地连出数招，一招比一招凌利！\n\n"NOR, me);
             me->add_temp("apply/attack",nh/2);
             me->add_temp("apply/damage",nh/3);
             }

        neili = (int)me->query("neili");
        me->set_temp("ljz/riyue", neili);
        me->add("neili", -nh*20);    
        check_fight(me, nh);
        me->start_exert(nh, "「日月」");
        return 1;

}

int check_fight(object me, int nh)
{    

        if( !me || !(int)me->query_temp("ljz/riyue")) return 0;

        if( me->is_ghost()|| !living(me))
          me->delete_temp("ljz/riyue");
          
        if( !me->is_fighting()
         || me->query("neili") <= 10
         || (userp(me)
         && me->query_skill_mapped("force") != "linji-zhuang"))
		call_out("remove_effect", 1, me, nh);
        else {
           if(me->query("neili") < (int)me->query_temp("ljz/riyue")){
             tell_object(me, "你体内日月之力运转不息，使你感觉不到任何内力的消耗！\n");
             me->set("neili", me->query_temp("ljz/riyue"));
           }
           call_out("check_fight", 1, me, nh);
        }       
        return 1;
}       

void remove_effect(object me, int nh)
{
        if( !me || !me->query_temp("ljz/riyue")) return;
	me->start_exert(0);
	me->delete_temp("ljz/riyue");
	message_vision(HIR"$N所聚天地之精气已散回日月之间，$N又恢复了原有的气力消耗。\n\n"NOR, me);

        if( me->query("emjiuyin")) {
             message_vision(HIY"$N的峨嵋九阴总诀无法维系，招式渐渐慢了下来。\n"NOR, me);
             me->add_temp("apply/attack",-nh/2);
             me->add_temp("apply/damage",-nh/3);
             }

}
