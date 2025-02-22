// gangrou.c 太极拳「刚柔诀」诀
// by snowman@SJ 26/11/1999
// Modified by snowman@SJ 08/05/2001


inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI	"/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() {return 1;}
string perform_name(){ return HIR"刚柔诀"NOR; }

int perform(object me, object target)
{ 
	if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「刚柔诀」只能对战斗中的对手使用。\n");

	if( userp(me) 
        &&( me->query_skill_mapped("parry") != "taiji-quan"
        && me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("「刚柔诀」必须在用太极拳或太极剑激发招架的情况下才能使用。\n");
        if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill_prepared("cuff") != "taiji-quan") )
                return notify_fail("你的内功或拳法不对，根本不能发挥出「刚柔诀」的优势。\n");  
        if( !me->query_temp("tj/太极") && me->query_skill("taiji-quan", 1) < 300 )
                return notify_fail("太极拳精要在于立如秤准，活如车轮，你没有运用「太极」，又如何能使用「刚柔诀」？\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你现在真气不够，强行使用「刚柔诀」是发挥不了它的威力的！\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     
        
        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
        int damage = 1, j;
        string msg, str;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 1000 || me->query("jingli") < 200 || me->query_temp("weapon")){
        	write("你目前用不了「刚柔诀」。\n");
		return 1;
        }                

	if( target->query_condition("neishang") ){
		write("对方已经身受内伤，你不必再用「刚柔诀」了。\n");
		return 1;
	}
	if(intp(me->query_temp("tjq/"+target->query("id")) > 4))
		me->add_temp("tjq/"+target->query("id"), -4);
	else me->delete_temp("tjq/"+target->query("id"));
	              
        str = (string)me->query("env/六合劲"); 
        if(str != "钻翻" && str != "螺旋" && str != "软手" && str != "开合" && str != "静恒" && str != "虚灵")
        	str = "无";
        	
        msg = HIB"\n$N使出太极拳中"RED"「刚柔诀」"HIB"的功夫，";
        
        if(me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill("yinyun-ziqi", 1) < 100){
        	msg += "右手一翻，拍向$n！\n"NOR;
        	str = "无";
        }        
        
        else msg += "右手一掌拍向$n，中和元气，拳路随意所之，意之所向，变化犹龙！人莫能测，运用在心，此是太极真诀！\n"NOR;
        
        if( TAIJI->check_force(target) == str || me->query_skill("taiji-quan", 1) > 350 )
        	damage = 2;
       
        me->start_perform(4, "「刚柔诀」");
        
	me->start_busy(1);
	if(!target->is_busy()) target->start_busy(1);
	if( random(me->query("combat_exp") / 100 * me->query_kar()) 
	> (int)target->query("combat_exp") / 200 * target->query_kar()){
		msg += HIY"$n眼见$P攻来，嘿嘿一笑，抬手就封住了$N这一掌！\n"NOR;
		call_out("hurt", 0, target, damage);	
	}
	
	else if( random(me->query("combat_exp") / 100 * me->query_kar()) 
	< (int)target->query("combat_exp") / 100 * target->query_kar() ){
		damage *= (me->query_skill("cuff") + me->query("jiali")) * 2;
		target->receive_damage("qi", damage, me);
        	target->receive_wound("qi", damage/4, me);
        	j = (int)target->query("qi")*100/(int)target->query("max_qi");
        	msg += damage_msg(damage, "内伤")+"( $n"+eff_status_msg(j)+" )\n"; 
	}
        else{
		msg += HIY"可是$p经验老到，脚下一退，闪开了「刚柔诀」！\n"NOR;
	}

        message_vision(msg, me, target);
        return 1;
}


int hurt(object target, int damage)
{
        string msg;

        if( !target || !target->is_character() )
                return 0;
                
        msg = HIR"突然$N全身一震，气息翻腾，原来是被「刚柔诀」左手的柔劲抚到了！\n"NOR;
        if( target->query("neili") <= 50 || target->query("qi") <= 100 ){
		tell_object(target, "你猛然发觉自己真气已然枯竭耗尽，无法运劲相抗了！\n");
		msg += RED"结果只见$N猛地口中鲜血狂喷，全身骨骼碎裂，眼见是活不成了！！\n"NOR;
		target->receive_damage("qi", (int)target->query("qi")+1, "内伤发作");
		target->set("eff_qi", 10);
                msg += "( $N"+eff_status_msg(1)+" )\n";   
		message_vision(msg, target);
	}
	
	else if( target->query_skill("force") > 450 ) 
		target->apply_condition("neishang", 7 * damage);
	else target->apply_condition("neishang", 13 * damage);
	message_vision(msg, target);
        return 1;
}

int help(object me)
{
	write(WHT"\n太极「刚柔诀」："NOR"\n");
	write(@HELP
	使太极拳「刚柔诀」，其为气也，至大至刚，直养无害，充塞天地，配义与
	道，端由集义，浑灏流行，自然一气。轻如杨花，坚如金石，虎威比猛，鹰
	扬比疾。行同乎水流，止伴乎山立。伤敌于内，可破横练、气猛之对手。
	
	要求：	内力 1000 以上；      
		精力 200 以上；      
		运用太极拳意且手无兵器。
HELP
	);
	return 1;
}