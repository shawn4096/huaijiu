// hero 英雄三招
// 19991002001

#include <ansi.h>

inherit F_SSERVER;

int calc_damage(int,int);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,j,k,total,shen; 
        
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("「英雄三招」只能在战斗时使用！\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「英雄三招」只有拜了教主后才能用！\n");

        if( objectp(weapon=me->query_temp("weapon")) ) {
                string *ids = weapon->parse_command_id_list();
                if (member_array("bishou", ids) == -1)                          
                        return notify_fail("你必须拿着匕首才能用「英雄三招」！\n");
        }
        else {
                return notify_fail("你必须拿着匕首才能用「英雄三招」！\n");
        }
        
        if( (int)me->query_skill("huagu-mianzhang", 1) < 150 )
                return notify_fail("你的化骨绵掌还不够熟练，不能使用「英雄三招」！\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("只有使用化骨绵掌时才能使用「英雄三招」！\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 150 )
                return notify_fail("你的神龙腿法还不够熟练，不能使用「英雄三招」！\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("只有使用神龙腿法时才能使用「英雄三招」！\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 150 )
                return notify_fail("你的沧浪钩法还不够熟练，不能使用「英雄三招」！\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("只有使用沧浪钩法时才能使用「英雄三招」！\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 150 )
                return notify_fail("你的毒龙大法功力不足，不能用「英雄三招」。\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用「英雄三招」！\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("你现在内力不足，不能使用「英雄三招」！\n");      

        if(me->query("gender")!= "男性") 
                return notify_fail("只有男人才能使用「英雄三招」！\n");      

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你现在所使用的内功同毒龙大法向抵触，不能使用「英雄三招」。\n");

        target->start_busy(1);
        me->add("jingli",-100);
        me->add("neili",-200);

        i = (me->query_skill("hook", 1) + me->query_skill("strike", 1) + me->query_skill("leg", 1)) /3 ;
        j = (target->query_skill("force", 1) + target->query_skill("dodge", 1) + target->query_skill("parry", 1))/3;

        shen = me->query("shen");
        if ( shen >= 0 && shen > me->query("combat_exp")) shen = me->query("combat_exp");
        if ( shen < 0 && - shen > me->query("combat_exp")) shen = - me->query("combat_exp"); 

        k = -shen / 3000;

        if(k > 1000) k=1000;
        if(k < -1000) k=-1000;

        i = i * (1000 + k/3)/1000;
        k = 1000 + random(k/2);

        if(wizardp(me)) tell_object(me,sprintf("\nattack: %d , parry: %d  , shen: %d \n",i,j,k));

        msg = HIR"$N乘$n稍稍走神之机，拼尽全力使出洪教主不传之绝技－－「英雄三招」\n"NOR;

        if(random(me->query("combat_exp")) > target->query("combat_exp")/2) {
                me->start_busy(1);
                me->add("neili",- random(400)+400 );
                me->add("jingli",-random(200)+ 200);
                total = 0;
                msg += HIY "\n$N使出一招「子胥举鼎」，一手轻搔$n腋底极泉穴，乘其慌张之际，另一手同\n"+
                           "时拿向$n肘后小海穴，将其摔向地上。\n\n"NOR;
                i = calc_damage(me->query_skill("huagu-mianzhang",1),k);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"瘀伤");
                result = replace_string( result, "$l", "小海穴" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     

                msg =HIY "\n$N使出一招「鲁达拔柳」，缩腿假装向$n叩头，突然一个斛斗，似欲向$n胯下\n"+
                         "钻过，但只一作势，左手抓向$n右脚足踝，右手兵器虚点向$n小腹，一用力，把$n头下\n"+
                         "脚上，倒提起来。\n"NOR;

                i = calc_damage(me->query_skill("canglang-goufa",1),k);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"刺伤");
                result = replace_string( result, "$l", "小腹" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     

                msg =HIY "\n$N使出一招「狄青降龙」，背脊后撞，十指向$n胸口虚抓，乘其避让之际，\n"+
                         "突然一个倒翻斛斗，身子跃起，双腿一分，跨坐在$n肩头，同时双手拇指压住$n\n"+
                         "太阳穴，食指按眉，中指按眼。\n"NOR;

                i = calc_damage(me->query_skill("shenlong-tuifa",1),k);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"内伤");
                result = replace_string( result, "$l", "头部" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                me->start_perform(6,"「英雄三招」");
        }
        else {
                msg += HIY "\n$N使出一招「子胥举鼎」，一手轻搔$n腋底极泉穴，乘其慌张之际，另一手同\n时拿向$n肘后小海穴，将其摔向地上。\n"NOR;
                msg += "但是$n看破了$N的企图，没有上当，急急忙忙向旁边一闪，躲了过去。\n";
                msg +=HIY "\n$N使出一招「鲁达拔柳」，缩腿假装向$n叩头，突然一个斛斗，似欲向$n胯下\n"+
                          "钻过，但只一作势，左手抓向$n右脚足踝，右手兵器虚点向$n小腹，一用力，把$n头下\n"+
                          "脚上，倒提起来。\n"NOR;
                msg += "$n吃了一惊，但随即冷静下来，在空中猛一蹬腿踢向$N面门，$N只得松开了手。\n";
                msg += HIY "\n$N使出一招「狄青降龙」，背脊后撞，十指向$n胸口虚抓，乘其避让之际，\n"+
                           "突然一个倒翻斛斗，身子跃起，双腿一分，跨坐在$n肩头，同时双手拇指压住$n\n"+
                           "太阳穴，食指按眉，中指按眼。\n"NOR;
                msg += "$n被$N制住，但临危不乱，以内力护住要害，同时高高跃起，翻身以头撞地，把$N撞了出去！\n";

                message_vision(msg,me,target);

                me->start_busy(1+random(3));
                me->start_perform(4,"「英雄三招」");
        }

        return 1;
}

int calc_damage(int skill,int k)
{
        int i;

        if(skill>200)
                i = (200*3 + (skill-200)*4) * k/1000;
        else
                i = (skill * k/1000) * 5;

        i = i/2 + random(i/2);

        if(i > 800) i = 800;
        return i;
}
