// xianglong-zhang.c 降龙十八掌

#include <ansi.h>
inherit SKILL;


string *parry_msg = ({
"$p不待回身，半招「神龙摆尾」，做势反劈。$P见这招势凶狠，不敢硬接，纵身避开。\n",
"只见$p左掌圆劲，右掌直推，挡在身前。一招纯是防御，却是在双方之间布了一道坚壁。\n",
"$p当下不敢怠慢，双掌当胸平推，将自己全身笼罩在掌力之下。守得稳若渊停岳峙，直无半点破绽。\n",
});

string query_parry_msg(object weapon, object victim) 
{ 
        if ( victim->query_temp("weapon") || victim->query_skill("xianglong-zhang", 1) < 100
        || victim->query_skill_prepared("strike") != "xianglong-zhang" )
                return SKILL_D("parry")->query_parry_msg(weapon);
        else
                return parry_msg[random(sizeof(parry_msg))];
}

mapping *action = ({
([      "action": "$N双腿微曲，双掌平平提到胸前，右臂划个圆圈，呼的一声，用降龙十八掌的第一招「亢龙有悔」拍向$n",
        "dodge": 10,
        "force": 250,
        "lvl" : 0,
        "skill_name": "亢龙有悔",
        "damage_type": "瘀伤"
]),
([      "action": "$N突然一跃飞起半空，身形急速旋转，居高临下，双掌使出一招「飞龙在天」，夹杂着汹涌的罡气直向身下的$n压去",
        "dodge": -5,
        "force": 270,
        "lvl" : 10,
        "skill_name": "飞龙在天",
        "damage_type": "瘀伤"
]),
([      "action": "但见$N一招未完，一招又起，左掌回收护胸，右掌向右横推而出，这是一招「见龙在田」，迅捷无比地劈向$n的$l",
        "dodge": -10,
        "force": 290,
        "lvl" : 20,
        "skill_name": "见龙在田",
        "damage_type": "瘀伤"
]),
([      "action": "$N凝神闭气，提起双掌齐胸平推，施出「鸿渐于陆」，这招外表看似平凡朴实，但掌力夹却带着隐隐的风声，缓缓压向$n",
        "dodge": -5,
        "force": 310,
        "lvl" : 30,
        "skill_name": "鸿渐于陆",
        "damage_type": "瘀伤"
]),
([      "action": "$N右掌聚成拳状，一式炮锤格开$n的手臂，接着近身上前左掌迅速推出，这是一招「潜龙勿用」，掌力雄浑涌向$n",
        "dodge": -10,
        "force": 330,
        "lvl" : 40,
        "skill_name": "潜龙勿用",
        "damage_type": "内伤"
]),
([      "action": "爆喝声中$N飞身上前，单掌凝气，凌空劈出一招「利涉大川」，这降龙掌掌风如刀如刃，迅猛无比地砍向$n的$l",
        "dodge": 5,
        "force": 350,
        "weapon" : "降龙掌掌风",
        "skill_name": "利涉大川",
        "lvl" : 50,
        "damage_type": "割伤"
]),
([      "action": "$N双掌相并，身体突然前跃，使出「突如其来」这招，掌力排山倒海般向$n正面推出，逼无可逼",
        "dodge": -5,
        "force": 350,
        "skill_name": "突如其来",
        "lvl" : 60,
        "damage_type": "瘀伤"
]),
([      "action": "突见$N猛然大吼一声，中宫空门大开，双掌一上一下劈出两道惊人的劲，不顾一切地斩击$n，这是一招「震惊百里」",
        "dodge": -25,
        "force": 370,
        "skill_name": "震惊百里",
        "lvl" : 70,
        "damage_type": "瘀伤"
]),
([      "action": "$N跨前一步，一招「或跃在渊」，左右双掌向$n连连拍出，一浪接着一浪，掌风更带起地上无数沙石",
        "dodge": -10,
        "force": 370,
        "skill_name": "或跃在渊",
        "lvl" : 70,
        "damage_type": "瘀伤"
]),
([      "action": "$N身形向前移动，双掌分使两式「双龙取水」，凌厉的掌风一左一右，但却不分先后，同时压向$n$l",
        "dodge": -10,
        "force": 390,
        "skill_name": "双龙取水",
        "lvl" : 80,
        "damage_type": "瘀伤"
]),
([      "action": "$N左脚微曲，身形飞起，于半空中拍出「鱼跃于渊」，双掌立砍，斧一般的掌劲齐向$n的$l劈下",
        "dodge": -5,
         "force": 390,
        "weapon" : "手掌",
        "skill_name": "鱼跃于渊",
        "lvl" : 90,
        "damage_type": "割伤"
]),
([      "action": "$N扎个马部，使出一招「时乘六龙」，双掌一正一反，一上一下，一前一后向$n周身连连续续猛烈砍了六下",
        "dodge": -10,
        "force": 410,
        "skill_name": "时乘六龙",
        "lvl" : 100,
        "damage_type": "瘀伤"
]),
([      "action": "$N使出一招「密云不雨」，左掌将掌力连连拍出，带起旋风封住$n了的退路，右掌跟着斜斜地劈向$n的$l",
        "dodge": -10,
          "weapon" : "降龙掌掌力",
        "skill_name": "密云不雨",
        "force": 410,
        "lvl" : 110,
        "damage_type": "割伤"
]),
([      "action": "$N弓步向前，使出一招「损则有孚」，双掌看似软绵绵地拍向$n，但劲力过处，地上的沙石连连飞舞，着实潜力不小",
        "dodge": -15,
        "force": 430,
        "skill_name": "损则有孚",
        "lvl" : 120,
        "damage_type": "内伤"
]),
([      "action": "$N脚下一转，突然欺身到$n身前，右掌斜转护住全身，左掌运劲一招「龙战于野」，猛然砍向$n的$l",
        "dodge": -5,
        "weapon" : "掌缘",
        "skill_name": "龙战于野",
        "force": 430,
        "lvl" : 130,
        "damage_type": "割伤"
]),
([      "action": "$N一声爆喝，胸前门户大开，双掌相并，齐向$n猛地推去，正是一招至刚的「履霜冰至」，至自己于死地而不顾",
        "dodge": -25,
        "force": 480,
        "skill_name": "履霜冰至",
        "lvl" : 140,
        "damage_type": "瘀伤"
]),
([      "action": "$N左掌低垂，右掌抬高，使出一招「羝羊触蕃」，两股雄浑的掌力打出，一上一下同时向中间的$n挤压下去",
        "dodge": 5,
        "force": 500,
        "skill_name": "羝羊触蕃",
        "lvl" : 150,
        "damage_type": "瘀伤"
]),
([      "action": "但见$N左掌护胸，身体一侧，后转背对$n，右掌紧跟着一摆，一招「神龙摆尾」拍向身后的$n",
        "dodge": 15,
        "force": 500,
        "skill_name": "神龙摆尾",
        "lvl" : 160,
        "damage_type": "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练降龙十八掌必须空手。\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 100)
                return notify_fail("你的混天气功火候不够，无法练降龙十八掌。\n");
        if( me->query("gender") == "无性")
                return notify_fail("你一个不男不女之人怎能学习降龙掌？\n");
        if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力太弱，无法学降龙十八掌。\n");
        if ((int)me->query_str() < 27 )
                return notify_fail("你没有雄壮的臂力无法学降龙十八掌。\n");
        if ((int)me->query_con() < 26)
                return notify_fail("你没有雄厚的体质无法学降龙十八掌。\n");

        return 1;
      }

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, j, level, tmp; 
            
        level   = (int) me->query_skill("xianglong-zhang",1);
    
        if (me->query_temp("slbw")) {   
                me->delete_temp("slbw");             
                return ([  
                        "action" : HIC"但见$N硬接了$p这一招，右掌紧接着向后一摆，一招「神龙摆尾」出其不意地按在了$n的$l上！"NOR,
                        "force" : me->query("gender")=="男性"?600:450,
                        "dodge": me->query("gender")=="男性"?30:20,
                        "parry": me->query("gender")=="男性"?30:20,
                        "damage_type" : "瘀伤",
                        ]);
                }
    
        else if ( me->query_temp("xlz/hanglong")){
                me->delete_temp("xlz/hanglong");
                tmp = 2 + random(level/10);
                return ([
                        "action": YEL"\n$N叫道：「看招！」左腿微屈，右掌划了个圆圈，平推出去，正是降龙十八掌中的「亢龙有悔」。"+
                        "初推出去看似轻描淡写，但一遇阻力，刹时之间连加"+ chinese_number(tmp)+ "道後劲，一道强似一道，重重叠叠，直至无"+
                        "坚不摧，无强不破！"NOR,
                        "dodge": -30 + 10 * tmp,
                        "parry": -25 + 10 * tmp,
                        "force": 500 + 40 * tmp,        
                        "damage": 50 + 10 * tmp,
                        "damage_type": random(2)?"内伤":"瘀伤" ]);
                }
                
        for(i = sizeof(action); i > 0; i--) {
                if(level > action[i-1]["lvl"]) {
                        j = NewRandom(i, 20, level/5);       
                        if (me->query_temp("xlz/xiao") && me->query("jiali") >= 50 )                 
                                return ([  
                                "action" : HIY+action[j]["action"]+NOR,
                                "force" : (me->query("gender")=="男性"?action[j]["force"]:action[j]["force"]/2)+me->query_str()*5,
                            "dodge":(me->query("gender")=="男性"?action[j]["dodge"]:action[j]["dodge"]+10)+random(10),
                                "parry": me->query("gender")=="男性"?30:10,
                                "lvl" : action[j]["lvl"],
                                "weapon" : action[j]["weapon"],
                                "damage_type" : action[j]["damage_type"],
                                ]);
                      
                else return ([  
                        "action" : action[j]["action"],
                        "force" : me->query("gender")=="男性"?action[j]["force"]:action[j]["force"]/2,
                        "dodge":me->query("gender")=="男性"?action[j]["dodge"]:action[j]["dodge"]+20,
                        "parry": me->query("gender")=="男性"?10:5,
                        "lvl" : action[j]["lvl"],
                        "weapon" : action[j]["weapon"],
                        "damage_type" : action[j]["damage_type"],
                        ]);
                }
        }
}       

int practice_skill(object me)
{
        int lvl = (int)me->query_skill("xianglong-zhang", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("jingli") < 100)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 40)
                return notify_fail("你的内力不够练降龙十八掌。\n");

        me->receive_damage("jingli", 60);
        me->receive_damage("neili", 20);
        if(lvl > 150) 
                me->receive_damage("jingli", 10);
        if(lvl > 200) 
                me->receive_damage("neili", 10);
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"xianglong-zhang/" + action;
}


int ob_hit(object ob, object me, int damage)
{
        int i, neili;
        if(living(me) &&
        userp(me) &&
        random(me->query_str()) > ob->query_str()/4 &&
        random(me->query("combat_exp")) > ob->query("combat_exp")/10 &&
        me->query_skill("xianglong-zhang", 1) >= 180 && 
        me->query("neili") > 600 &&
        me->query("eff_qi") < me->query("max_qi")/2 &&
        !me->query_temp("slbw_hit") &&
        !ob->query("env/invisibility"))
        {
                me->set_temp("slbw", 1);
                ob->set_temp("slbw_hit", 1);
                i = me->query("jiali");
                neili = me->query("neili");
                me->set("jiali", me->query_skill("force") + 100);
                me->add_temp("apply/attack", me->query_skill("xianglong-zhang", 1)/2);
                me->add_temp("apply/strength", i/2);
                
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);
                
                if(me->query("neili") < neili) me->set("neili", neili-100);
                me->set("jiali", i);
                ob->delete_temp("slbw_hit");
                me->add_temp("apply/attack", -me->query_skill("xianglong-zhang", 1)/2);
                me->add_temp("apply/strength", -i/2);
        }
        
        return 1;
}
