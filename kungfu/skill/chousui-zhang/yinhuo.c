#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
int check_pfm(object me, object target, object ob);
int perform(object me, object target)
{
      object ob;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「银火」攻击只能对战斗中的对手使用。\n");
      
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「银火」！\n");        
        if(!objectp(ob = present("huo yan", environment(me))))
                return notify_fail("没有火堆怎么驱动「银火」进行攻击？\n");
        if(me->query_temp("pfm_chousui"))
                return notify_fail("你正在驱动火堆进行攻击！\n");

       message_vision(YEL"\n$N衣袖一拂，一股劲气直射入"HIR"火焰"YEL"之中。从中又分出一道细细的"WHT"银火"YEL"，便似一条"WHT"银色长蛇"YEL"
横卧空际，轻轻摆动，颜色又是鲜艳，又是诡异，"RED"光芒"YEL"闪烁不定！\n"NOR,me);
       me->set_temp("pfm_chousui", 1);
       if(random(me->query_kar()) > 3)
             check_pfm(me, target, ob);
       else call_out("check_pfm", 2, me, target, ob);
       return 1;
}

int check_pfm(object me, object target, object ob)
{
        string msg, *limbs;
        int i, neili, ap, dp, damage, p;
        object wep;
        if(!me) return 0;        
        i = (int)me->query_skill("chousui-zhang", 1);
        neili = (int)me->query("neili");        

        me->delete_temp("pfm_chousui");
        me->start_busy(1);
        if(!living(me) || me->is_ghost()) return 1;
        
        if(!objectp(present(ob, environment(me)))){
           message_vision(HIY"$N眼看火堆熄灭，长叹一声，散开内息，双手下垂而立。\n"NOR,me);
           return 1;
        }
        
        if( i < 140 ){
                tell_object(me, "你发现自己的星宿毒掌还不够娴熟，无法使用「银火」进行攻击。\n");
                return 1;
                }
        if( (int)me->query_skill("huagong-dafa",1) < 140 ){
                tell_object(me,"你发现自己的化功大法修为不够，无法使用「银火」进行攻击。\n");
                return 1;
                }
        if((int)me->query_skill("poison",1) < 110){
                tell_object(me,"你发现自己体内聚毒不够，无法使用「银火」进行攻击。\n");         
                return 1;
                }
        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang"){
                tell_object(me,"你必须用抽髓掌才能使用「银火」进行攻击。\n"); 
                return 1;
                }                                                                                
        if( me->query_skill_mapped("force") != "huagong-dafa"){
                tell_object(me,"你发现自己所用的内功无法进行「银火」攻击。\n");
                return 1;
                }
        if( (int)me->query("max_neili") < 1200) {
                tell_object(me,"你发现自己内力太弱，无法驱动「银火」进行攻击。\n");
                return 1;
                }
        if(neili < 900){
                tell_object(me,"你发现自己现在真气太弱，使不出「银火」进行攻击。\n");           
                return 1;
                }
        if(!target || !living(target)
           || !me->is_fighting(target)
           || environment(me)!=environment(target)){
           message_vision(HIY"$N衣袖再拂，将升起的"WHT"银火"HIY"压回火焰之中。\n"NOR,me);
           return 1;
           }
       

        ap = me->query("combat_exp")/1000 * i * me->query_str();
        dp = target->query("combat_exp")/1000 * target->query_skill("parry",1) * target->query_str();
        if (ap < 1) ap = 1;
        if (dp < 1) dp = 1;
        me->add("neili", -500);
        me->add("jingli", -50);

        msg = YEL"\n突然火焰中升起"GRN"绿色鬼火"YEL"，此时"WHT"银火"YEL"倏地缩回，跟着又向$n$l射去，力道极猛，去势奇快！\n"NOR;        

       
        if(random(ap+dp) > dp){
        	me->start_busy(2);
		if(objectp(wep = target->query_temp("weapon")) && random(2)==1){     
            		msg += HIY"看那银火来得迅猛无常，避无可避，只得把手中武器举起来硬挡！\n" NOR;
            		if(me->query("neili") < target->query("neili")/2)
                   		msg += HIY"结果只听一声大响，$w"HIY"在$W"HIY"上撞出无数飞花，四散溅开！\n" NOR;
                   	
            		else if(me->query("neili") > target->query("neili")/2*3){
                   		if(wep->query("rigidity") >= 1){
                      			target->start_busy(4);
                      			wep->unequip();
                      			wep->move(environment(target));
                      			msg += HIW"结果只听“嘣”的一声，在$w"HIW"的猛烈撞击下，$n虎口震裂，$W"HIW"脱手飞出！\n" NOR;
                      			target->reset_action();
                      		}
                   		else{
                      			target->start_busy(2);
                      			msg += HIW"结果只听“啪”的一声巨响，$n手中"+wep->name()+HIW"被$w"HIW"打断，碎片四散溅落！\n" NOR;
                      			wep->unequip();
                      			wep->move(environment(target));
                      			wep->set("name", "断掉的" + wep->query("name"));
                      			wep->set("value", 49);
                      			wep->set("weapon_prop", 0);
                      			target->reset_action();
                      		}
                  	}
            		else {
                   		if(wep->query("rigidity") >= 1){
                      			target->start_busy(4);
                      			msg += HIY"结果只听一声大响，$w在$W上撞出无数飞花，四散溅开！\n" NOR;
                      		}
                   		else{
                      			target->start_busy(2);
                      			wep->unequip();
                      			wep->move(environment(target));
                      			msg += HIW"结果只听“嘣”的一声，在$w"HIW"的猛烈撞击下，$n虎口震裂，$W"HIW"脱手飞出！\n" NOR;
                      		}
                  	}
            	msg = replace_string(msg, "$W", wep->name());
        	}
        
        	else{
                	damage = (i+me->query("jiali"))*4;
                	if(neili > target->query("neili")*2) damage *= 2;
                        if( damage > 2000 ) damage = 2000;
                	target->receive_damage("qi", damage, me);    
                	target->receive_wound("qi", damage/2, me);            
                	target->apply_condition("xx_poison", random(3) + (me->query_skill("poison", 1)/10) + target->query_condition("xx_poison"));
			if (userp(me) && userp(target) && me->query_condition("killer") < 15 && 
		  me->query_temp("kill_other/"+target->query("id")) && target->query_temp("other_kill/"+me->query("id")))
				me->apply_condition("killer", 15);
                	p = (int)target->query("qi")*100/(int)target->query("max_qi");
                	msg += damage_msg(damage, "刺伤");
                	msg += "( $n"+eff_status_msg(p)+" )\n";
                	target->start_busy(3);
                }
        }
        
        else{
          	me->start_busy(3);
          	msg += HIY"\n$p全力向右一滚，那$w"HIY"堪堪擦肩而过，端的是凶险无比！\n" NOR;
        }
        
       limbs = target->query("limbs");
       msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
       msg = replace_string(msg, "$w", WHT"银火"NOR);   
       if(!target->is_killing(me->query("id"))) target->kill_ob(me);    
       message_vision(msg, me, target);
       return 1;
}  

