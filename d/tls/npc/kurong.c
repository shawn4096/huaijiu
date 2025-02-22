//update by cool 98.2.18

inherit F_MASTER;
inherit NPC;

int ask_xingyue(object who);
string ask_liumai1();
string ask_liumai2();
int ask_dudan(object who);   

void create()
{
     object ob;
        set_name("枯荣长老", ({ "kurong zhanglao","kurong","zhanglao"}) );
        set("nickname", "天龙寺长老");
         set("long", 
" 枯荣长老面容奇特之极，左边的一半脸色红润，
皮光肉滑，有如婴儿，右边的一半却如枯骨，除了
一张焦黄的面皮之外全无肌肉，骨头突了出来，宛
然便是半个骷髅骨头。他在天龙寺中辈份最高，在
这里独参枯禅已数十年，天龙寺诸僧众，谁也没见
过他真面目。\n");
        set("gender", "男性" );
        set("class","bonze");   
        set("unique", 1);
        set("age", 99);
        set("str", 30);
        set("cor", 27);
        set("cps", 32);
        set("int", 25);
        set("per",23);
        set("max_jing",5000);
        set("eff_jingli",3500);
        set("max_qi",7000);
        set("jiali",100);
        set("neili",15000);
        set("max_neili",15000); 
        set("rank_info/respect", "高僧");
        create_family("天龙寺", 12, "僧侣");
        set("combat_exp", 2850000);
        set("score", 0);
        set("chat_chance_combat", 60);
        set("chat_msg_combat",({ 
                (: exert_function, "ku" :),
                (: perform_action, "finger.sandie" :),
        }));
        set_skill("parry", 300);
        set_skill("dodge", 300);
        set_skill("medicine", 180);
        set_skill("force", 200);
        set_skill("finger", 300);
        set_skill("whip", 300);
        set_skill("liumai-jianzhen",200);
        set_skill("cihang-bian", 300);
        set_skill("duanjia-jianfa", 300);
        set_skill("sword", 300);
        set_skill("strike", 300);
        set_skill("buddhism", 200);
        set_skill("literate", 200);
        set_skill("qiantian-yiyang", 220);
        set_skill("liumai-shenjian", 40);
        set_skill("kurong-changong", 220);
        set_skill("qingyan-zhang", 280);
        set_skill("yiyang-zhi", 300);
        set_skill("tianlong-xiang", 300);
        map_skill("whip", "cihang-bian");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "kurong-changong");
        map_skill("finger", "yiyang-zhi");
        map_skill("strike","kurong-changong");
        map_skill("force", "kurong-changong");
        prepare_skill("finger","yiyang-zhi"); 
        set_temp("apply/armor", 60);
        set_temp("apply/attack", 60);
        set_temp("apply/damage", 60);
        set("inquiry", ([
        "name": "贫僧就是枯荣",
     "菩提" : (: ask_xingyue :),
         "毒丹" : (: ask_dudan :),
        "普云洞" : (: ask_liumai2 :),
        "段誉" : (: ask_liumai1 :),
        ]) );

        set("env/一阳指", 3);
        setup();
        
        if (clonep(this_object()))  {
        if (ob = carry_object("/clone/weapon/xingyue")) ob->wield(); }
        carry_object("/d/tls/obj/jiasha")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}
#include "kurong.h"

