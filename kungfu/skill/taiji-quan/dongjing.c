// dongjing.c 太极拳「动静诀」诀
// by snowman@SJ 02/03/2000
// Modified by snowman@SJ 24/05/2001

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI                "/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() { return 1;}
string perform_name(){ return HIR"动静诀"NOR; }

int perform(object me, object target)
{ 
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「动静诀」只能对战斗中的对手使用。\n");

	if( userp(me) 
        &&( me->query_skill_mapped("parry") != "taiji-quan"
        && me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("「动静诀」必须在用太极拳或太极剑激发招架的情况下才能使用。\n");
        if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill_prepared("cuff") != "taiji-quan") )
                return notify_fail("你的内功或拳法不对，根本不能发挥出「动静诀」的优势。\n");  
        if( !me->query_temp("tj/太极") && me->query_skill("taiji-quan", 1) < 300 )
                return notify_fail("太极拳精要在于动急则急应，动缓则缓随，你没有运用「太极」，又如何能使用「动静诀」？\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你现在真气不够，强行使用「动静诀」是发挥不了它的威力的！\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     
        if( target->query_condition("no_exert") )
                return notify_fail("( 对方气息不匀，看来是已经不能施用内功了。)\n");
                        
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
                
        if(intp(me->query_temp("tjq/"+target->query("id")) > 3))
                me->add_temp("tjq/"+target->query("id"), -3);
        else me->delete_temp("tjq/"+target->query("id"));
        
        str = (string)me->query("env/六合劲"); 
        if(str != "钻翻" && str != "螺旋" && str != "软手" && str != "开合" && str != "静恒" && str != "虚灵")
                str = "无";
                
        msg = MAG"\n$N使出太极拳中"RED"「动静诀」"MAG"的功夫，";
        
        if(me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill("yinyun-ziqi", 1) < 100){
                msg += "突然一下冲到$n面前，要抓住$n！\n"NOR;
                str = "无";
        }        
        
        else msg += "静之则合，无过不及，随曲就伸，让$n搭住自己的双手！\n"NOR;
        
        if(TAIJI->check_force(target) == str || me->query_skill("taiji-quan", 1) > 350)
                damage = 3;
       
        me->start_perform(2, "「动静诀」");
        if(!stringp(force = to_chinese(target->query_skill_mapped("force"))))
                force = "内功";
        
        if(wizardp(me) && (string)me->query("env/combat")=="verbose")
                tell_object(me, "Str = "+str+"，Force = "+force+"，Damage = "+damage+"\n");
        
        if( random(me->query("combat_exp") * (me->query_str() + me->query_int())/ 100) 
        > (int)target->query("combat_exp") * (target->query_str() + target->query_dex()) / 200 
        || target->is_busy() ){
                msg += HIY"$p哈哈一笑，就要起手向$P击落！\n"NOR;
                me->start_perform(3+random(2), "「动静诀」");
                me->start_busy(1);
                if(!target->is_busy()) target->start_busy(3);
                call_out("hurt",1+random(2),  me, target, damage, str, force);  
        }
        
        else{
                msg += HIY"可$p毕竟感觉不对，马上退后放开了$P的手腕！\n"NOR;
                me->start_busy(1+random(2));
        }

        message_vision(msg, me, target);
        return 1;
}

int hurt(object me, object target, int damage, string str, string force)
{
        object weapon;
        string msg;
        int p;
        
        if( !me || !living(me) || me->is_ghost() || !me->is_fighting()) return 0;
        
        if( !target || !target->is_character() || !me->is_fighting(target) || damage < 1
        || environment(target)!=environment(me) )
                return 0;
        
        msg = MAG"\n太极者，无极而生；动之则分，静之则合！";
        switch(str){
                case "钻翻": msg += "$N双手一翻，反搭住$n，太极拳的"HIW"「"+str+"劲」"MAG"猛然冲开"+force+"使出，将$n一送，甩了出去！\n"NOR;break;
                case "螺旋": msg += "$N反手一旋，抓住$n，"HIW"「"+str+"劲」"MAG"透入$n护身的"+force+"一纽，抓起$p从肩背上甩了出去！\n"NOR;break;
                case "软手": msg += "$N将"HIW"「"+str+"劲」"MAG"一送，震散了$p的"+force+"，刚好又在$n要急力挣脱时一抖一放，让$p自己摔了一大交！\n"NOR;break;
                case "开合": msg += "$N双掌一分，带着"HIW"「"+str+"劲」"MAG"当胸撞$n，让$p的"+force+"来不及反应！\n"NOR;break;
                case "静恒": msg += "$N双掌不动，全身"HIW"「"+str+"劲」"MAG"催动，一下子就破掉了$n的"+force+"，还将$p震得站立不稳！\n"NOR;break;
                case "虚灵": msg += "$N立如秤准，活如车轮，运起"HIW"「"+str+"劲」"MAG"带动$n的"+force+"一送，让$p马步不稳，全力都打向空处！\n"NOR;break;
                default: msg = MAG"\n$N突然反手拉住$n双掌一送一震，破了$p的内功气劲！\n"NOR;break;
        }    
        
        if (target->query("neili") <= 200){
                message_vision(msg, me, target);
                tell_object(target, "你发觉自己真气已然枯竭耗尽，根本无法相抗了！\n");
                target->receive_damage("qi", (int)target->query("qi")+1, me);
                msg = RED"结果$N措手不及，被自己的劲力震得头昏目眩，摇摇欲坠！\n"NOR;
                msg += damage_msg(target->query("max_qi"), "摔伤") + "( $N"+status_msg(5)+" )\n"; 
                message_vision(msg, target, target);
                me->start_busy(1);
                return 1;
        }
        
        
        else if(me->query("neili")*3 < target->query("neili")) 
        {
                me->start_busy(2+random(3));
                target->start_busy(1+random(2));
                
                msg += HIR"不料$p内力雄厚，经验老到，顺势一冲，从$P身边擦过！！\n"NOR;   
                message_vision(msg, me, target);
                return 1;
        }
        
        p = (int)me->query_skill("force") + random(me->query_skill("force")*2);
        target->receive_damage("qi", p, me);
        target->receive_wound("qi", p/2, me);
        msg += damage_msg(p, "摔伤")+
        "( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n"; 
        
        message_vision(msg, me, target);
        
        if(wizardp(me) && (string)me->query("env/combat")=="verbose") 
                tell_object(me, "Damage ="+p+"\n");

        if(random(2) == 1 && !wizardp(me)){
                if( !me->is_killing(target->query("id"))
                && !target->is_killing(me->query("id"))
                && !me->query("have_master")   // added by snowman
                && target->query("qi")*2 <= target->query("max_qi")) 
                        COMBAT_D->end_fight(me, target);
                return 1;
        }
        
        if(wizardp(me) && (string)me->query("env/combat")=="verbose") 
                tell_object(me, "Dongjing done.\n");
                
        force = target->query_skill_mapped("force");
        
        switch(force){
                case "huntian-qigong":
                        if( intp(p = target->query_temp("htqg/powerup")) ){
                                target->add_temp("apply/attack", - p);
                                target->add_temp("apply/dodge", - p);
                                target->delete_temp("htqg/powerup");
                                tell_object(target, HIR"你的混天气功被一下震散，提升的效应也消失了！\n"NOR);
                                break;
                        }
        
                case "yijin-jing":
                        if( intp(p = target->query_temp("fanzhen")) ){
                                p = target->query_temp("fanzhen");
                                target->add_temp("apply/armor", - p);
                                target->delete_temp("fanzhen");
                                target->delete_temp("no_skill_hit_ob");
                                tell_object(target, HIR"你的「金刚不坏体神功」被一下震散，效应也相应地消失了！\n"NOR);
                                break;
                        }
        
                case "linji-zhuang":
                        if( target->query_temp("ljz/riyue") ){
                                target->delete_temp("ljz/riyue");
                                tell_object(target, HIR"你的「日月」庄被一下震散，效应也消失了！\n"NOR);
                                break;
                        }
                        if( intp(p = target->query_temp("ljz/yinyang")) ){
                                target->add("max_qi", - p);
                                target->receive_wound("qi", p, "「阴阳」庄被破，脱力而");
                                target->delete_temp("ljz/yinyang");
                                tell_object(target, HIR"你的「阴阳」庄被一下震散，提升的效应也消失了！\n"NOR);
                                break;
                        }
                        if( intp(p = target->query_temp("ljz/fengyun")) ){
                                target->add_temp("apply/dexerity", - p);        
                                target->delete_temp("ljz/fengyun");
                                tell_object(target, HIR"你的「风云」庄被一下震散，提升的效应也消失了！\n"NOR);
                                break;
                        }
                        if( intp(p = target->query_temp("ljz/wuwo")) ){
                                target->add_temp("apply/armor", -p);
                                target->add_temp("apply/defense", -p);
                                target->add_temp("apply/parry", -p);
                                target->delete_temp("ljz/wuwo");
                                tell_object(target, HIR"你的「无我」心法被一下震散，提升的效应也消失了！\n"NOR);
                                break;
                        }
                case "yinyun-ziqi":
                        if( target->query_temp("tj/太极") ){
                                target->delete_temp("tj/太极");
                                tell_object(target, HIR"你在慌忙之中，太极不能连贯而行，效应也消失了！\n"NOR);
                                break;
                        }
                case "dulong-dafa":
                        if( intp(p = target->query_temp("sld/wudi2") ) ){
                                target->add_temp("apply/attack", - p/2*3);
                                target->add("max_qi",- target->query_temp("sld/wudiqi"));
                                target->delete_temp("sld");
                                if(target->query("eff_qi") > target->query("max_qi")) 
                                        target->set("eff_qi",target->query("max_qi"));
                                tell_object(target, HIR"你给这「动静诀」一震，心神一松，再也支持不住了！！\n"NOR);
                                if(random( target->query("qi")) < 100) 
                                        target->unconcious();
                                break;
                        }
                        else if( intp(p = target->query_temp("sld/wudi")) ){
                                target->add("max_qi",- target->query_temp("sld/wudiqi"));
                                target->add_temp("apply/attack", -p);
                                target->delete_temp("sld/wudiqi");
                                target->delete_temp("sld/wudi");
                                if(target->query("eff_qi") > target->query("max_qi")) 
                                        target->set("eff_qi",target->query("max_qi"));
                                tell_object(target, HIR"你给这「动静诀」一震，心神一松，好象虚脱了一样，突然垮了下来！！\n"NOR);
                                break;
                        }
                case "hanbing-zhenqi":
                        if( objectp(weapon = target->query_temp("weapon")) 
                        && weapon->query("jianqi") == target){
                                weapon->create();
                                weapon->set("weapon_prop/damage", weapon->query("old_damage"));
                                weapon->delete("jianqi");
                                tell_object(target, HIR"你给这「动静诀」一震，心神一松，这「嵩山剑气」便使不下去了！\n"NOR);
                                break;
                        }
                case "huagong-dafa":
                        if( intp(p = target->query_temp("hgdf/judu")) ){
                                target->add_temp("apply/armor", -p);           
                                target->delete_temp("hgdf/judu");
                                tell_object(target, HIR"你给这「动静诀」一震，心神一松，所聚毒素全都垮了！！\n"NOR);
                                break;
                        }
                        else if( intp(p = target->query_temp("hgdf/huadu")) ){
                                target->add_temp("apply/attack", -p); 
                                target->add_temp("apply/armor_vs_force", -p/2);           
                                target->delete_temp("hgdf/huadu");
                                tell_object(target, HIR"你给这「动静诀」一震，心神一松，化毒所聚毒素全都垮了！！\n"NOR);
                                break;
                        }
                case "yunu-xinjing":
                        if( target->query_temp("xinjing") ){
                                p  = target->query_temp("xinjing/eff");
                                target->add_temp( target->query_temp("xinjing/bonus"), -p/5);
                                target->delete_temp("xinjing");
                                tell_object(target, HIR"你的「心经」字决被神功震散，效应也消失了！\n"NOR);
                                break;
                        }
                case "longxiang-boruo":
                        if ( intp(p = target->query_temp("xs/shield")) ) {
                                target->add_temp("apply/dodge", -p);
                                target->add_temp("apply/armor", -p);
                                target->delete_temp("xs/shield");
                                tell_object(target, HIR"你被「动静诀」一震，脸上红光一闪，骨节啪啪轻响几声，散去了护体真气。\n" NOR);
                                break;
                        }
                case "qiantian-yiyang":
                        if( intp(p = target->query_temp("dali_jing")) ){
                                target->add_temp("apply/intelligence", -p);
                                target->delete_temp("dali_jing");
                                tell_object(target, HIR"你被「动静诀」一震，无法继续潜修了。\n" NOR);
                                break;
                        }
                case "kurong-changong":
                        if( intp(p = target->query_temp("pf_ku")) ){
                                target->delete_temp("pf_ku");
                                target->add_temp("apply/armor", -p); 
                                tell_object(target, HIR"你被「动静诀」一震，「枯」字大法立刻消散了！\n" NOR);
                                break;
                        }
                        else if( intp(p = target->query_temp("pf_rong")) ){
                                p = target->query_temp("pf_rong");
                                target->delete_temp("pf_ku");
                                target->add_temp("apply/strike", -p/5);
                                target->add_temp("apply/damage",-p/6);
                                tell_object(target, HIR"你被「动静诀」一震，「荣」字大法立刻消散了！\n" NOR);
                                break;
                        }
                case "bihai-chaosheng":
                        if ( intp(p = target->query_temp("thd/maze")) ){
                                target->add_temp("apply/defense", - (p/5));
                                target->delete_temp("thd/maze");
                                if(weapon = target->query_temp("thd/maze_target") && weapon->query_temp("thd/mazed")){
                                        weapon->delete_temp("thd/mazed");
                                        weapon->add_temp("apply/dexerity", p/10);
                                        weapon->add_temp("apply/dodge", p/10);
                                        weapon->add_temp("apply/damage", p/10);
                                        tell_object(weapon, target->name() + "对你布的迷阵已经被"+me->name()+"的「动静诀」震散了。\n");
                                }
                                tell_object(target, HIR"你被「动静诀」一震，布的迷阵瞬间消散了！\n" NOR);
                                break;
                        }
        }
        
        target->apply_condition("no_exert", me->query_skill("taiji-quan", 1)/15+1);
        if( !me->is_killing(target->query("id"))
        && !target->is_killing(me->query("id"))
        && !me->query("have_master")   // added by snowman
        && target->query("qi")*2 <= target->query("max_qi")) 
                COMBAT_D->end_fight(me, target);
        return 1;
}

int help(object me)
{
	write(WHT"\n太极「动静诀」："NOR"\n");
	write(@HELP
	太极拳经讲：动之则分，静之则合。无过不及，随曲就伸。立如秤准，活如
	车轮，偏沉则随，双重则滞。动静诀便是一以静制动，以动制静之绝招，吸
	引对手进前，伺机反制，不但能创伤对手，还能有效地破除对方的各类内功。
	
	要求：	内力 1000 以上；      
		精力 200 以上；      
		运用太极拳意且手无兵器。
HELP
	);
	return 1;
}
