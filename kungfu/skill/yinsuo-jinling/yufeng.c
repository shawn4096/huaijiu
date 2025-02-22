// yufeng.c 银索金铃--玉蜂针
// By River
inherit F_SSERVER;
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
       string msg;
       object ob,weapon = me->query_temp("weapon");
       int i, damage, p;
      
       if( !target ) target = offensive_target(me);

       if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
             return notify_fail("玉蜂针只能对战斗中的对手使用。\n");

       if( !weapon || me->query_skill_mapped("whip") != "yinsuo-jinling") 
             return notify_fail("你现在无法使用玉蜂针攻击对方。\n");

       if(!objectp( ob= (present("yufeng zhen", me))))
             return notify_fail("你身上没有玉蜂针，怎么使用玉蜂针？\n");

       if((int)me->query_skill("yunu-xinjing", 1)  < 121 )
             return notify_fail("你的玉女心经等级还不够，使不出玉蜂针。\n");

       if((int)me->query_skill("yinsuo-jinling",1) < 121 ) 
             return notify_fail("你的银索金铃还不够娴熟，不会使用玉蜂针。\n");

       if((int)me->query_skill("throwing",1) < 101 ) 
             return notify_fail("你的暗器功夫还不够娴熟，不会使用玉蜂针。\n");

       if((int)me->query("neili") < 500)
             return notify_fail("你的内力不够用来动手。\n");

       if( userp(me) && (string)me->query("family/master_name") != "小龙女")
             return notify_fail("你不是小龙女的弟子，怎么会使用玉蜂针！\n"); 

       msg = HIW"\n$N"+weapon->name()+HIW"交左手，右手袖袍一挥，一枚玉蜂针从袖底飞出直向$n急射而去。\n"NOR;
       me->start_busy(2);
       me->add("neili", -150);
       me->add("jingli", -60);
       i = (int)target->query_skill("dodge", 1) + (int)target->query_skill("parry", 1);
       i = random(i/2) - 10;
       damage = (int)me->query_skill("throwing", 1) + me->query_str()*2;

       if((int)me->query_skill("throwing", 1) > i
       && random(target->query("kar")) < 13 
       && (int)me->query("combat_exp") > (int)target->query("combat_exp")/2
       || !living(target)) {
          msg += HIR"$n猛见金光一闪，急忙闪身躲避，但听一声惨叫，结果仍是被玉蜂针刺中！\n"NOR;
          target->apply_condition("bee_poison", target->query_condition("bee_poison") + damage / 5);
          target->receive_wound("jing", damage/2);
          target->receive_damage("qi", damage + random(damage));
          target->receive_wound("qi", damage); 
          p = (int)target->query("qi")*100/(int)target->query("max_qi");
          msg += "( $n"+eff_status_msg(p)+" )\n";
          target->set_temp("last_damage_from", "被"+me->name()+"杀");
          me->start_perform(4,"玉蜂针");
       }
       else {
          msg +=CYN"$n急忙飞身后跃，只听嗤一声轻响，玉蜂针射在$p身前的泥土之中。\n"NOR;
          target->add("jingli", -10);
          me->add("neili",-50);
          me->start_busy(2);
          me->start_perform(3,"玉蜂针");
       }              
       message_vision(msg, me, target);
       if(!target->is_killing(me->query("id"))){
         me->kill_ob(target);
         target->kill_ob(me);
       }
       ob->add_amount(-1);
       return 1;
}
