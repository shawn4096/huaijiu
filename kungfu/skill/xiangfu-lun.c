// /kungfu/skill/xiangfu-lun.c
// xiangfu-lun.c 降伏轮
// dubei
// snowman(98,12,22)
// iceland(99.8.3)
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「大赞叹光明势」，右手立掌护胸，左手单臂抡起$w，当胸砍向$n的$l",
        "skill_name" : "大赞叹光明势",
        "force" : 170,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 0,
        "damage" : 70,
        "damage_type" : "割伤",
]),
([      "action" : "$N将手中$w抛上半空，跃起一掌砸在$w上，这招「大皈依光明势」有如流星坠地，直轰$n",
        "skill_name" : "大皈依光明势",
        "force" : 210,
        "dodge" : 10,
        "parry" : -10,
        "lvl" : 20,
        "damage" : 90,
        "damage_type" : "瘀伤",
]),
([      "action" : "凭空闪出一道雪白的光幕，光电闪烁中$w挟「大功德光明势」的无上劲力，从$N手中飞出砍向$n的$l",
        "skill_name" : "大功德光明势",
        "force" : 200,
        "dodge" : 5,
        "parry" : 10,
        "lvl" : 40,
        "damage" : 120,
        "damage_type" : "割伤",
]),
([      "action" : "$N双眼磕闭，全身衣物却在内劲鼓荡下涨如气球，那$w在这「大常乐光明势」的推动下，向$n缓缓压去",
        "skill_name" : "大常乐光明势",
        "force" : 220,
        "dodge" : -5,
        "parry" : 15,
        "lvl" : 60,
        "damage" : 65,
        "damage_type" : "内伤",
]),
([      "action" : "$N双手越转越急，光幕俨如一轮明月，将$n笼罩，这「大吉祥光明势」的劲力带着$w以排山倒海之势飞旋而出",
        "skill_name" : "大吉祥光明势",
        "force" : 240,
        "dodge" : -10,
        "parry" : -5,
        "lvl" : 80,
        "damage" : 80,
        "damage_type" : "砸伤",
]),
([      "action" : "$N口中高唱「降魔咒」，一招「大三昧光明势」挥出，$w幻化的漫天的轮影犹如行云流水般涌向$n",
        "skill_name" : "大三昧光明势",
        "force" : 260,
        "dodge" : 10,
        "parry" : -15,
        "lvl" : 100,
        "damage" : 100,
        "damage_type" : "瘀伤",
]),
([      "action" : "$N面现瑞气，以无上降魔大法催动「大般若光明势」，$w舞出的光云慢慢逼近$n。",
        "skill_name" : "大般若光明势",
        "force" : 280,
        "dodge" : -10,
        "parry" : 10,
        "lvl" : 120,
        "damage" : 120,
        "damage_type" : "瘀伤",
]),
([      "action" : "$N提一口真气，手中$w上下翻飞，轮番砸出，这「大智慧光明势」让$n眼前轮影乱舞，应接不暇。",
        "skill_name" : "大智慧光明势",
        "force" : 300,
        "dodge" : -20,
        "parry" : 10,
        "lvl" : 140,
        "damage" : 140,
        "damage_type" : "砸伤",
]),
([      "action" : "$N面带微笑，眼露慈光，全身所散发出的「大慈悲光明势」气劲宛如惊涛骇浪，$w一波接一波地涌向$n",
        "skill_name" : "大慈悲光明势",
        "force" : 320,
        "dodge" : 15,
        "parry" : 10,
        "lvl" : 160,
        "damage" : 160,
        "damage_type" : "瘀伤",
]),
([      "action" : "$N双手高举$w，大喝一声使出「大圆满光明势」自上而下斩向$n，其快绝无比，气势汹涌，已达圆满之境",
        "skill_name" : "大圆满光明势",
        "force" : 350,
        "dodge" : 20,
        "parry" : -15,
        "lvl" : 180,
        "damage" : 200,
        "damage_type" : "刺伤",
]),
});

string *parry_msg = ({
MAG"$n不躲不避，手中法轮摆开，在$N跟前形成了一道光幕，$N此招根本无法递出。\n"NOR,
MAG"却见$n踏前一步，手中法轮翻飞，力道威猛，$N见势心怯，闪身而退。\n"NOR,
MAG"$n轮法突变，法轮带着风声飞舞出去，后发先至，在$N还没攻出时就破了$N的招数。\n"NOR,
MAG"但见$n力贯双臂，举法轮硬架，乒的一声震开了来势汹汹的$N。\n"NOR,
MAG"$n看准来势，法轮摆个天地势，将$N进路封死，$N这招只发得一半就攻不进去了。\n"NOR,
MAG"$N一招运足，才发现$n手中法轮指向自己的$l，正是此招的空门，连忙收招闪避。\n"NOR,
});

string  *msg = ({
CYN"$w"CYN"已彷佛幻化成了千百条般挥舞不息，漫天的轮影形成了一个多角形的图案，每一轮的攻出都是如此凌厉而猛辣"NOR,
HIY"空中那几只法轮对击，声若龙吟，悠悠不绝，就在$n一呆之际，法轮飞砸了出去！"NOR,
YEL"呜呜声响中，法轮旋转飞舞着撞向$n，在$p便要挡隔时，却绕过他飞到了身後"NOR,
YEL"$w"YEL"法轮连续掷出，连续飞回，绕著$n兜个圈子，忽高忽低，或正或斜，所发声音也是有轻有响，旁观众人均给扰得眼花撩乱，心神不定"NOR,
YEL"一声「小心了！」，蓦然间法轮合体归一，并排向$n撞去，势若狂牛冲阵，威不可挡"NOR,
HIC"蓦而$n身前五丈方圆内起了一阵回旋的风暴，光华灿然中，法轮飞舞而出，几似龙降九天"NOR,
HIG"这些$w"HIG"好似彼比连接在一起的巨龙，在$n身前盘旋纵横，鳞甲闪烁，好像宇宙之间，已全被这所遮掩无馀"NOR,
MAG"只见$w"MAG"呜呜响声不绝，绕著$n上下翻飞，掀的阵阵狂风有如刀割，似要把$n从中劈开"NOR,
YEL"突然狂风大作，激荡中那$w"YEL"相碰相撞，数轮归一，合并了向$n砸去"NOR,
HIM"法轮再次合围，紫电精芒围著$n的四周旋舞闪射，千百轮影幻映出一幅美丽而眩目的图案，这图案美极了，似是一片多角形的紫色雪晶体"NOR,
YEL"法轮在$n身前环饶，猛地向$p迎头击下，接着又飞来一轮，一抄一送，呜呜声响，兜向$n$l"NOR,
YEL"呼呼飞啸声中，那几只法轮或直飞、或斜飞、或回旋、或下坠、或上升，霎时间$n的全部退路已被封死"NOR,
BLU"猛地里$w"BLU"向$n$l飞砸下，在$p沉肩卸避之时，法轮又突然上飞击出，砸向$p的$l"NOR,
YEL"那法轮飞旋砸到，$n却并不回头，听风辨器，一一挡开，但法轮便如长上了眼睛一般，竟然又旋飞到了$n$l"NOR,
HIY"随着森森慑人的厉吼，$w"HIY"蓦而急颤晃动，轮身嗡嗡震响，在不及眨眼的瞬息间，耀目的电光金蛇四射迸闪，飞掠周遭，迅捷无匹的击$n"NOR,
});
int valid_enable(string usage) { return usage == "hammer" || usage == "parry"; }

void skill_improved(object me)
{
        int skill = me->query_skill("xiangfu-lun", 1);
        if(skill >= 200 && !me->query("ryl_add")){
                me->set("ryl_add", 1);   
                tell_object(me, HIW"\n忽然，你感道内息越转越快，瞬时功力已经上升到了一个新的境界！\n你的精气增加了！\n你的臂力增加了！\n"NOR);
                me->add("max_jingli", skill/2+random(skill));
                me->add("max_neili",skill/2+random(skill));
        }
}
int valid_learn(object me)
{
        if((int)me->query_str() <=35)
                return notify_fail("你的臂力不够学降伏轮。\n");
        if((int)me->query("max_neili") < 2000)
                return notify_fail("你的内力不够。\n");
        if((int)me->query_skill("longxiang-boruo", 1) <= 160)
                return notify_fail("需要有第八层以上龙象般若功火候,才能学降伏轮。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int) me->query_skill("xiangfu-lun",1);
        
        if( !userp(me) && me->query("env/invisibility")
        && me->query("master_user/user") ){
                return ([
                        "action": msg[random(sizeof(msg))],
                        "damage":(random(4)+1)*60,
                        "damage_type":random(2)?"砸伤":"瘀伤",
                        "dodge": 5,
                        "force":250+random(250)
                ]);
        }

        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

mixed query_parry_msg(object weapon, object me, int attack_type)
{
        if (objectp(weapon = me->query_temp("weapon")) 
        && (string)weapon->query("skill_type") == "hammer"
        && me->query_skill_mapped("hammer") == "xiangfu-lun"
        && me->query_skill_mapped("parry") == "xiangfu-lun")
		return parry_msg[random(sizeof(parry_msg))];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
            || (string)weapon->query("skill_type") != "hammer")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("你的现在的内力不足,无法继续练降伏轮。\n");
        me->receive_damage("jingli", 40);
        me->add("neili", -20); 
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xiangfu-lun/" + action;
}

mixed hit_ob(object me, object victim,int damage)
{
        object wp1, wp2; 

        wp1 = me->query_temp("weapon");
        
        if( !objectp(wp2= victim->query_temp("weapon")) )
                return;
                
        if( !me->query("env/锁")
        || me->query_skill("xiangfu-lun", 1) < 150 
        || !me->query("jiali")
        || me->query("neili") < 1000 
        || me->query_skill_mapped("parry") != "xiangfu-lun" )
                return;
        if( random(10) >= 6 
        && random(me->query("combat_exp")) > victim->query("combat_exp")/3*2 ){
                message_vision(HIW"$N手臂暴长，施展「锁」字诀，"+wp1->name()+HIW"探出，嚓的一声锁住了$n"+wp2->name()+HIW"。\n"NOR, me,victim);
                if( random(me->query_str()) > victim->query_str() ){           
                        me->add("neili", -150);
                        message_vision(HIG+me->query("name")+"运劲回拉，$N臂骨喀的一声，险些就被拉断，剧痛之下手一松，"+wp2->name()+HIG"被夺了过去！\n"NOR, victim);
                        wp2->unequip();
                        wp2->move(me);
                }

                else if(random(me->query_str()) > victim->query_str()/3*2){           
                        me->add("neili", -50);
                        message_vision(HIG+me->query("name")+"运劲回拉，$N被带得踉跄几步，但觉虎口剧痛，"+wp2->name()+HIG"脱手飞出！\n"NOR, victim);
                        wp2->unequip();
                        wp2->move(environment(victim));
                }

                else if( me->query_temp("shield") ){           
                        me->add("neili", -50);
                        message_vision(HIY"$N借势前冲，"+wp2->name()+HIY"直刺过去，但被"+me->query("name")+"护体真气荡得滑了开去。\n"NOR, victim);
                }

                else message_vision(HIY"$N借势前冲，"+wp2->name()+HIY"直刺"+me->query("name")+"，"+me->query("name")+"变招奇快，"+wp1->name()+HIY"一抖松脱，纵身退了开去。\n"NOR, victim);
        }
}
