// fengyun.c

#include <ansi.h>

int exert(object me)
{       
        int improve;

        if( !me->is_fighting() )
            return notify_fail("你只能在战斗中运用临济十二庄的「风云」字决！\n");

        if( me->query("class") != "bonze" && me->query("family/generation") > 3)
            return notify_fail("你不是出家人，无法领会临济十二庄的「风云」字决！\n");
        
        if((int)me->query_skill("linji-zhuang", 1) < 90)
            return notify_fail("你的临济十二庄修为还不够。\n");

        if((int)me->query("neili") < 200 )
            return notify_fail("你的真气不够。\n");
        
        if( me->query_temp("ljz/fengyun")   )
            return notify_fail("你正在运用临济十二庄的「风云」字决！\n");

        tell_object(me,MAG"你暗运风云两庄，心思浮云飘空之悠闲缓慢，默想狂风荡地之迅速紧急一股丹田热气分注四肢百骸，但觉身手敏捷了许多。\n"NOR, me);
        tell_room(environment(me), MAG"只见"+me->name()+"微闭双眼，身旁凝起一圈白雾，瞬息间一股旋风卷过，身形又复清晰。\n"NOR,({ me }));
        improve = (int)me->query("dex") ;
        me->add_temp("apply/dexerity", improve);
        me->set_temp("ljz/fengyun", improve);  
        me->add("neili", - 150);    
        me->start_perform(2,"「风云」字决");
        me->start_exert(2,"「风云」字决");
        call_out("remove_effect", 1, me, (int)me->query_skill("dodge", 1)/2 );
        return 1;
}

void remove_effect(object me,int count)
{
        int i;
        if(!me || !me->query_temp("ljz/fengyun")) return;
        if( ! me->is_fighting()
         || count < 1){
          i = me->query_temp("ljz/fengyun");
          me->add_temp("apply/dexerity", -i);
          me->delete_temp("ljz/fengyun");
          tell_object(me, HIR"你风云行功已久，略觉步履沉重了一些。\n"NOR);
          return;
        }
        call_out("remove_effect", 1, me,count - 1);
}
