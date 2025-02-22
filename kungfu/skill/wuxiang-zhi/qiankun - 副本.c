// qiankun.c 
// tiantian@sj 2000.10.14 
// Modified by snowman@SJ 12/12/2000

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      	string msg;
      	int improve;

      	if( !target ) target = offensive_target(me);
     
      	if( !target )
          	return notify_fail("你要对谁使用「袖里乾坤」？\n");

        if( me->query("family/family_name")!="少林派" )
                return notify_fail("你不是少林弟子，如何能使用少林绝技？\n");
        if( me->query("shen")<0 )
                return notify_fail("你心术不正，不能使用慈悲为怀的少林武功？\n");
        if(me->query_condition("killer")>200)
                return notify_fail("一日不过三，别杀上瘾了。\n");
        if(environment(me)->query("no_fight"))
                return notify_fail("这里不能攻击别人。\n");
        if(target->query("combat_exp")<100000)
                return notify_fail("这么差的人，用得着如此费劲么？\n");
          
      	if( objectp(me->query_temp("weapon")) )
          	return notify_fail("你必须空手使用「袖里乾坤」！\n");
      
      	if( (int)me->query_skill("wuxiang-zhi",1) < 200 )
          	return notify_fail("你的无相劫指不够娴熟，不会使用「袖里乾坤」！\n");

      	if( (int)me->query_skill("yijin-jing",1) < 200 )
          	return notify_fail("你的易筋经内功等级不够，不能使用「袖里乾坤」！\n");  
      
      	if( (int)me->query("max_neili") < 3000 )
          	return notify_fail("你的内力太弱，不能使用「袖里乾坤」！\n");
      
      	if( (int)me->query("neili") < 3000 )
          	return notify_fail("你的内力太少了，无法使用出「袖里乾坤」！\n");   
                                                                                 
      	if (me->query_skill_prepared("finger") != "wuxiang-zhi"
       	|| me->query_skill_mapped("finger") != "wuxiang-zhi")
          	return notify_fail("你现在无法使用「袖里乾坤」进行攻击。\n");                                                                                 
        if( me->query_temp("slpfm/jgqbrz") )
                return notify_fail("你正在使用少林绝技「"+me->query_temp("slpfm/jgqbrz")+"」！\n");
        if( me->query_temp("slpfm/rytqys") )
                return notify_fail("你正在使用少林绝技「"+me->query_temp("slpfm/rytqys")+"」！\n");
        if( me->query_temp("slpfm/lzgyzc") )
                return notify_fail("你正在使用少林绝技「"+me->query_temp("slpfm/lzgyzc")+"」！\n");

      	if (target->is_corpse() || !target->is_character())
               	return notify_fail("那不是活物耶！\n");
        if(!living(target))
                return notify_fail("对方都这样了，还用的着这么费劲么？\n");

      	if(  target->is_busy() ) 
                return notify_fail("对方正自顾不暇，放胆攻击吧！\n");

      	me->set_temp("slpfm/lzgyzc","袖里乾坤");
      	me->set_temp("slpfm/jgqbrz","袖里乾坤");
      	me->set_temp("slpfm/rytqys","袖里乾坤");

      	me->start_perform(5, "袖里乾坤");
      	tell_object(me, HIY"你面带微笑，将双手拢在衣袖之中，指力从衣袖中暗暗发出，一股若有若无的微风向着"
		+target->name()+"袭去。\n" NOR);  
      	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, improve :), 6 );
        if( me->query("combat_exp") / 5 * 3 > random(target->query("combat_exp"))) {
        	tell_object(me,"结果"+target->query("name")+"被你指风点中，登时动弹不得。\n");
       		tell_object(target,"你只觉得一股若有若无的微风从身上拂过，不经意间发现自己已经无法动弹。\n");
            	me->add("neili", -350);    
            	target->start_busy(4 + random(me->query_skill("wuxiang-zhi",1))/40);
      	} else {
        	if( me->query_skill("wuxiang-zhi", 1)/3*2 > random(target->query_skill("dodge",1))){
                        msg = HIY"$n只觉得一股若有若无的微风从身上拂过，却又不知道发生了什么事情。\n"NOR;
                        me->start_busy(1+random(2));
                } else {
                        msg = HIY"$n只觉得一股若有若无的微风从身上拂过，回头看去，原来是$N在实施暗算。\n"NOR;
                        me->start_busy(2+random(3));
                        me->kill_ob(target);
                        target->kill_ob(me);
                }
                message_vision(msg, me, target);  
		me->add("neili", -200);
      }
      return 1;
}

void remove_effect(object me, int improve)
{
   	me->delete_temp("slpfm/lzgyzc");
        me->delete_temp("slpfm/rytqys");
        me->delete_temp("slpfm/jgqbrz");
}
