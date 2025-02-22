// yinyang.c 太极拳「阴阳诀」诀
// by snowman@SJ 26/02/2000
// Modified by snowman@SJ 24/05/2001

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI                "/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() {return 1;}
string perform_name(){ return HIR"阴阳诀"NOR; }

int perform(object me, object target)
{ 
	if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「阴阳诀」只能对战斗中的对手使用。\n");

	if( userp(me) 
        &&( me->query_skill_mapped("parry") != "taiji-quan"
        && me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("「阴阳诀」必须在用太极拳或太极剑激发招架的情况下才能使用。\n");
        if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill_prepared("cuff") != "taiji-quan") )
                return notify_fail("你的内功或拳法不对，根本不能发挥出「阴阳诀」的优势。\n");  
        if( !me->query_temp("tj/太极") && me->query_skill("taiji-quan", 1) < 300 )
                return notify_fail("太极者，无极而生，阴阳之母也，你没有运用「太极」，又如何能使用「阴阳诀」？\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你现在真气不够，强行使用「阴阳诀」是发挥不了它的威力的！\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     
        
        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
        int damage = 1;
        string msg, force, str;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 300 || me->query("jingli") < 100 || me->query_temp("weapon"))
        	return 0;     
                
        if(intp(me->query_temp("tjq/"+target->query("id")) > 4))
		me->add_temp("tjq/"+target->query("id"), -4);
	else me->delete_temp("tjq/"+target->query("id"));
	
        str = (string)me->query("env/六合劲"); 
        if(str != "钻翻" && str != "螺旋" && str != "软手" && str != "开合" && str != "静恒" && str != "虚灵")
        	str = "无";
        	
        msg = GRN"\n$N使出太极拳中"RED"「阴阳诀」"GRN"的功夫，";
        
        if(me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill("yinyun-ziqi", 1) < 100){
        	msg += "运起氤氲紫气，罩住$n！\n"NOR;
        	str = "无";
        }        
        
        else msg += "划了一个圆圈，左掌阳，右掌阴，搭向$n双手！\n"NOR;
        
       	if( TAIJI->check_force(target) == str || me->query_skill("taiji-quan", 1) > 350 )
        	damage = 3;
       
        me->start_perform(3, "「阴阳诀」");
        if(!stringp(force = to_chinese(target->query_skill_mapped("force"))))
        	force = "内功";
        	
        if(wizardp(me) && (string)me->query("env/combat")=="verbose")
		tell_object(me, "Str = "+str+"，Force = "+force+"，Damage = "+damage+"\n");
	
	if( random(me->query("combat_exp") * me->query_con() / 100) 
	> (int)target->query("combat_exp") * target->query_con() / 250 
	|| target->is_busy() ){
		msg += HIY"$n眼看不对，急中生智奋力一挣！\n"NOR;
		me->start_perform(6, "「阴阳诀」");
		me->start_busy(3);
		if(!target->is_busy()) target->start_busy(3);
		call_out("hurt",3,  me, target, damage, str, force, target->query("jiali"));	
	}
	
        else{
		msg += HIY"可是$p竟然眼明耳快，一个倒飞跳出了「阴阳诀」的范围！\n"NOR;
		me->start_busy(1+random(2));
	}

        message_vision(msg, me, target);
        return 1;
}

int hurt(object me, object target, int damage, string str, string force, int jiali)
{
        string msg;
	int i;
	
	if( !me || !living(me) || me->is_ghost() || !me->is_fighting()) return 0;
	
        if( !target || !target->is_character() || !me->is_fighting(target) || damage < 1
        || environment(target)!=environment(me))
                return 0;
        
        switch(str){
        	case "钻翻": msg = GRN"\n$N左手搭在$n右手上，右手搭在$p左手上，太极拳的"HIW"「"+str+"劲」"GRN"使出，顺势一送一翻，将$n双手的"+force+"碰在一起！\n"NOR;break;
        	case "螺旋": msg = GRN"\n$N双手将$n左右手抓住一转，使出「六合劲」中的"HIW"「"+str+"劲」"GRN"扯开$n护身"+force+"将他双手相碰！\n"NOR;break;
        	case "软手": msg = GRN"\n$N双手在$p手上一拍，$n马上回臂挡隔，结果"+force+"一下被"HIW"「"+str+"劲」"GRN"套住，双臂硬生生砸在一起！\n"NOR;break;
        	case "开合": msg = GRN"\n只见$N双掌飞翻，啪啪两声拍在$n双臂内侧，"HIW"「"+str+"劲」"GRN"带动$n的"+force+"，将$p双臂拉得咯咯直响！\n"NOR;break;
        	case "静恒": msg = GRN"\n$N双掌不动，$n一下打来，只觉全身"+force+"被"HIW"「"+str+"劲」"GRN"所笼罩，双臂无可闪避，砸在一起！\n"NOR;break;
        	case "虚灵": msg = GRN"\n$N双掌如云翻飞，忽然一下搭住$n双手，"HIW"「"+str+"劲」"GRN"无极而生，震得$n双臂的"+force+"碰在一起！\n"NOR;break;
        	default: msg = CYN"\n$N双手拉住$n双掌，将它们一下碰在一起！\n"NOR;break;
        }
        
        
        if (target->query("neili") <= 200){
        	message_vision(msg, me, target);
		tell_object(target, "你发觉自己真气已然枯竭耗尽，根本无法相抗了！\n");
		target->receive_damage("qi", (int)target->query("qi")+1, me);
		msg = RED"结果$N措手不及，被自己的劲力震得头昏目眩，摇摇欲坠！\n"NOR;
                msg += damage_msg(target->query("max_qi"), "震伤") + "( $N"+status_msg(5)+" )\n"; 
		message_vision(msg, target, target);
		me->start_busy(1);
        	return 1;
	}
	
	
	else if(me->query("neili")*3 < target->query("neili")) 
	{
		me->start_busy(2+random(3));
		target->start_busy(1+random(2));
                
		msg += HIR"不料$p内力雄厚，$P双手被反震开去，手臂麻木了半天！！\n"NOR;  
		message_vision(msg, me, target); 
        	return 1;
	}
	
	message_vision(msg, me, target);
	if(wizardp(me) && (string)me->query("env/combat")=="verbose") 
		tell_object(me, "Damage ="+damage+"\n");
	
	target->set_temp("must_be_hit", 1);
	target->set("have_master", 1);
	i = target->query("jiali");
	target->set("jiali", jiali);
        COMBAT_D->do_attack(target, target, target->query_temp("weapon"), damage);
        if( random(2) )
        	COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 1);
        target->set("jiali", i);
        target->delete("have_master");
        target->set_temp("last_damage_from", me);
	target->delete_temp("must_be_hit", 1);
	
        if( !me->is_killing(target->query("id"))
	&& !target->is_killing(me->query("id"))
	&& !me->query("have_master")   // added by snowman
	&& target->query("qi")*2 <= target->query("max_qi")) 
		COMBAT_D->end_fight(me, target);
		
        return 1;
}

int help(object me)
{
	write(WHT"\n太极「阴阳诀」："NOR"\n");
	write(@HELP
	太极拳经讲：太极者，无极而生，阴阳之母也。阴阳相济，方为懂劲。阴阳
	诀本身不带出手伤人之劲，但其内含阴阳，有力打无力，手慢让手快，是皆
	先天自然之能四两拨千斤也！故阴阳者，必拨敌之力，反制于敌。
	此招对付力大劲猛之敌最为有效，
	
	要求：	内力 1000 以上；      
		精力 100 以上；      
		运用太极拳意且手无兵器。
HELP
	);
	return 1;
}
