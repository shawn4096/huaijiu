// write by snowman@SJ

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
                return notify_fail("「火球」攻击只能对战斗中的对手使用。\n");
      
      	if( (int)me->query("max_neili") < 2500 ) 
                return notify_fail("你发现自己内力太弱，无法驱动「火球」进行攻击。\n");
        if( (int)me->query_skill("huagong-dafa",1) < 180 )
                return notify_fail("你发现自己的化功大法修为不够，无法使用「火球」进行攻击。\n");
        if( (int)me->query_skill("poison",1) < 150 )
                return notify_fail("你发现自己体内聚毒不够，无法使用「火球」进行攻击。\n");
        if( (int)me->query_skill("chousui-zhang", 1) < 180 )
                return notify_fail("你发现自己的星宿毒掌还不够娴熟，无法使用「火球」进行攻击。\n");
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「火球」！\n");        
        if( !objectp(ob = present("huo yan", environment(me))) )
                return notify_fail("没有火堆怎么驱动「火球」进行攻击？\n");
        if( me->query_temp("pfm_chousui") )
                return notify_fail("你正在驱动火堆进行攻击！\n");

       message_vision(HIR"\n$N厉声大喝，掌力加盛，火焰中突然生出一个斗大的"RED"火球"HIR"，在空中骨碌碌的迅速转动！\n\n"NOR,me);

       me->set_temp("pfm_chousui", 1);
       if(random(me->query_kar()) > 1)
             check_pfm(me, target, ob);
       else call_out("check_pfm", 4, me, target, ob);
       return 1;
}

int check_pfm(object me, object target, object ob)
{
        string msg, *limbs;
        int i, neili, ap, dp, damage, p;
        object *inv;
        
        if( !me ) return 0;
        me->delete_temp("pfm_chousui");
        
        if( !living(me) || me->is_ghost() ) return 0;
        
        if(!target 
        || !living(target) 
        || !me->is_fighting(target)
        || environment(me)!=environment(target)){
           	message_vision(HIY"$N衣袖再拂，将升起的"RED"火球"HIY"压回火焰之中。\n"NOR,me);
           	return 1;
        }  
        
        i = (int)me->query_skill("chousui-zhang", 1);
        neili = (int)me->query("neili");
        me->start_busy(2+random(2));
        
        if(!objectp(present(ob, environment(me)))){
           	message_vision(HIY"$N眼看火堆熄灭，散开内息，放下举起的双手。\n"NOR,me);
           	return 1;
        }
        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang"){
                tell_object(me,"你必须用抽髓掌才能使用「火球」进行攻击。\n"); 
                return 1;
        }                                                                                
        if( me->query_skill_mapped("force") != "huagong-dafa"){
                tell_object(me,"你发现自己所用的内功无法进行「火球」攻击。\n");
                return 1;
        }
        if(neili < 1000){
                tell_object(me,"你发现自己现在真气太弱，使不出「火球」进行攻击。\n");           
                return 1;
        }           
              

	ap = COMBAT_D->skill_power(me,"strike",SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target,"parry",SKILL_USAGE_DEFENSE);
        if(target->is_busy())
        	dp /= 2;
        if (ap < 1) ap = 1;
        if (dp < 1) dp = 1;
        me->add("neili", -600);
        me->add("jingli", -100);
	damage = ( i + me->query("jiali") ) * 10;
	if( ap < dp ) damage -= random(damage/3);
	if( ap > dp ) damage += random(damage/3);
	
        msg = WHT"\n此时$N脸上已无半点血色，一口口鲜血不住向"RED"火球"WHT"中吐去，"HIR"火势一盛，嗤嗤两声轻响，
爆出几朵火花，"RED"火球"HIR"陡然变大向$n疾冲过来！\n"NOR;

       
       	if(random(ap+dp) > dp || target->is_busy()){
       		target->add_condition("xx_poison", 30);
		if (userp(me) && userp(target) && me->query_condition("killer") < 15 && 
		  me->query_temp("kill_other/"+target->query("id")) && target->query_temp("other_kill/"+me->query("id")))
			me->apply_condition("killer", 15);
		if(!target->is_busy())
                	target->start_busy(2);
          	//inv = check_armor(all_inventory(target));
          	inv = filter_array(all_inventory(target),(:$1->query("equipped")=="worn":));
		inv -= ({0});
          	if( sizeof(inv) >= 1 ){     
            		if( neili > random(target->query("neili"))*2){
               			if( me->query_str()/3*2 > random(target->query_str()) ){
                  			msg += HIY"猛烈间火球温度飙升，火花迸射，炸开了$p的护具！\n" NOR;
                  			damage += random(damage)*2;
                  			damage -= target->query_temp("apply/armor");
                  			for(i=0; i<sizeof(inv); i++){
                     				inv[i]->unequip();
                         			inv[i]->move(environment(target));
                         			inv[i]->set("name", "粉碎的" + inv[i]->query("name"));
                         			inv[i]->delete("value");
                         			inv[i]->set("armor_prop", 0);
                         		}     
                  		}                   
            			else {
                  			msg += HIY"只见火球猛然升温，火花四溅，热力直透$p的护具！\n" NOR;
                  			damage += random(damage);
                  			damage -= target->query_temp("apply/armor");
                  			for(i=0; i<sizeof(inv); i++){
                     				inv[i]->set("name", "碎裂的" + inv[i]->query("name"));
                        			inv[i]->set("value", 49);
                         			if(inv[i]->query("armor_prop/armor"))
                             				inv[i]->set("armor_prop/armor", inv[i]->query("armor_prop/armor")/2);
                        		}
                  		}
                  		target->reset_action();     
               		}
          		else {
                  		msg += HIY"火球急速滚动，火光四溅，掀起阵阵火焰撞向$p怀里！\n" NOR;
                  	}
                  	target->receive_damage("qi", damage, me);   
                  	target->receive_wound("qi", damage/2, me);  
            	}
            	
        	else{
                //target has no armor, so, hehe...
                	if( neili > target->query("neili")/2*3 )
                		damage += random(damage);
                	else if( neili < target->query("neili")/3*2 )
                		damage -= random(damage/2);
                	else if( neili > target->query("neili")*2 ) 
                		damage *= 3;
                	damage += random(damage);
                	target->receive_damage("qi", damage, me);   
                	target->receive_wound("qi", damage/2, me);
                }
                p = (int)target->query("qi")*100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "砸伤");
               	msg += "( $n"+eff_status_msg(p)+" )\n";
               	limbs = target->query("limbs");
       		msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
       		msg = replace_string(msg, "$w", RED"火球"NOR);   
        }
        
    	else{
    		if(!target->is_busy())
        		target->start_busy(2);
        	msg += HIY"\n$p眼看就要被打中，冒死一个“铁板桥”，全身自膝盖处向后倒去，堪堪避过火球"HIY"！\n" NOR;
        }
            
       	message_vision(msg, me, target);
       	if( !target->is_killing(me->query("id")) ) target->kill_ob(me);
       	return 1;
} 

