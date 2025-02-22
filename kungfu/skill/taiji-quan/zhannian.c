// zhannian.c 太极拳「沾黏诀」诀
// by snowman@SJ 23/03/2000

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI                "/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() {       return 1;}
string perform_name(){ return HIR"沾黏诀"NOR; }

int perform(object me, object target)
{ 
	object ob;
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「沾黏诀」只能对战斗中的对手使用。\n");

	if( userp(me) 
        &&( me->query_skill_mapped("parry") != "taiji-quan"
        && me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("「沾黏诀」必须在用太极拳或太极剑激发招架的情况下才能使用。\n");
        if( userp(me) && ( me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill_prepared("cuff") != "taiji-quan") )
                return notify_fail("你的内功或拳法不对，根本不能发挥出「沾黏诀」的优势。\n");  
        if( !me->query_temp("tj/太极") && me->query_skill("taiji-quan", 1) < 300 )
                return notify_fail("太极拳精要在于动急则急应，动缓则缓随，你没有运用「太极」，又如何能使用「沾黏诀」？\n");
        if( (int)me->query("neili", 1) < 500 )
                return notify_fail("你现在真气不够，强行使用「沾黏诀」是发挥不了它的威力的！\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     
        if( target->is_busy())
                return notify_fail("对方正自顾不暇呢，你不忙使用「粘」字诀。\n");
        if( objectp(ob = me->query_temp("tjq/zhannian")) ) {
                if( ob->is_fighting(me) || me->is_fighting(ob))
                	return notify_fail("你已经在粘连粘随对手了。\n");
                else me->delete_temp("tjq/zhannian");
        }
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
                
        if(intp(me->query_temp("tjq/"+target->query("id")) > 2))
                me->add_temp("tjq/"+target->query("id"), -2);
        else me->delete_temp("tjq/"+target->query("id"));
        
        str = (string)me->query("env/六合劲"); 
        if(str != "钻翻" && str != "螺旋" && str != "软手" && str != "开合" && str != "静恒" && str != "虚灵")
                str = "无";
                
        msg = CYN"\n$N使出太极拳中"RED"「沾黏诀」"CYN"套向$n，";
        
        if(me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill("yinyun-ziqi", 1) < 100){
                msg += "手一挥，想要黏住$n！\n"NOR;
                str = "无";
        }        
        
        else msg += "一招一式节节贯串，如长江大河！\n"NOR;
        
  	if(TAIJI->check_force(target) == str )
                damage = 2;
       
        me->start_perform(3, "「沾黏诀」");
        if(!stringp(force = to_chinese(target->query_skill_mapped("force"))))
                force = "内功";
        
        if(wizardp(me) && (string)me->query("env/combat")=="verbose")
                tell_object(me, "Str = "+str+"，Force = "+force+"，Damage = "+damage+"\n");
        
        if( random(me->query("combat_exp")) * damage > target->query("combat_exp")/2 ){
        	msg += CYN"但见这粘劲一下"RED"「粘」"CYN"在$n身上，无论$p怎么摆脱，就是脱不出"HIW"「"+str+"劲」"CYN"的包围，一个圆圈跟着一个圆圈，大圈、小圈、平圈、立圈、正圈、斜圈，一个个太极圆圈发出，连绵不断，滔滔不绝！\n";
		tell_object(target, HIR"你一下子被"+me->name()+"黏住，退也不是，进也不是，搞了个手忙脚乱！\n"NOR);
                me->start_perform(2, "「沾黏诀」");
                me->set_temp("tjq/zhannian", target);
                me->start_busy(1);
                if(!target->is_busy()) target->start_busy(3);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), me->query_int()/2);      
        }
        
        else{
                msg += HIY"可$p经验老到，顺着$P也划出个圆圈，脱出了「沾黏诀」的包围！\n"NOR;
                me->start_busy(1+random(2));
        }

        message_vision(msg, me, target);
        return 1;
}

void remove_effect(object me)
{
	object ob;
	if( !me ) return;
	if( !objectp(ob = me->query_temp("tjq/zhannian")) ) return;
	
        me->delete_temp("tjq/zhannian");
        ob->delete_temp("lost_attack");
        if( me->is_fighting() )
        	message_vision(HIC"\n$N微微一笑，内劲轻转，「沾黏诀」收功而退。\n"NOR, me);
}

int help(object me)
{
	write(WHT"\n太极「沾黏诀」："NOR"\n");
	write(@HELP
	太极者，四两拨千斤之句，显非力胜；观耄耋御众之形，快何能为。立如秤
	准，活如车轮，偏沉则随，双重则滞。由招熟而渐悟懂劲，由懂劲而阶及神
	明。然非用力日久，不能豁然贯通焉。
	沾黏诀由太极推手练出，打斗中随敌而走，随敌而止，目的在于“困敌”。
	
	要求：	内力 500 以上；      
		精力 100 以上；      
		运用太极拳意且手无兵器。
HELP
	);
	return 1;
}
