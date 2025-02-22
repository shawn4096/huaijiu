//cool@SJ,990605
inherit F_MASTER;
inherit NPC;

string ask_kurong();

void create()
{
        set_name("本因大师", ({ "benyin dashi","benyin","dashi"}) );
        set("nickname", "天龙寺主持");
        set("long", "一位白须白眉的老僧，身穿一袭金丝木棉袈裟。
若以俗家辈份排列，本因大师应是当今大理国保
定帝的俗家叔父。\n");
        set("gender", "男性" );
        set("attitude", "friendly");
        set("age", 69);
        set("str", 25);
        set("int", 26);
        set("con", 28);
        set("dex", 26);
        set("unique", 1);
        set("class", "bonze");
        set("shen", 0);
        set("jing", 2000);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 100);
        set("qi", 3000);
        set("max_qi", 3000);
        set("neili", 3500);
        set("max_neili", 3500); 
        set("combat_exp", 1350000);
        set_skill("qiantian-yiyang", 165);      
        set_skill("tianlong-xiang", 165);       
        set_skill("yiyang-zhi", 150);
        set_skill("duanjia-jianfa",170);   
        set_skill("buddhism", 165);
        set_skill("literate", 120);
        set_skill("parry", 160);
        set_skill("finger", 165);
        set_skill("sword", 160);
        set_skill("dodge", 165);
        set_skill("kurong-changong", 100);
        set_skill("force", 160);
        set_skill("liumai-shenjian", 120);
        set_skill("medicine", 110);
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "yiyang-zhi");
        map_skill("sword", "duanjia-jianfa");
        map_skill("finger", "yiyang-zhi");
        prepare_skill("finger","yiyang-zhi");   
        create_family("天龙寺", 13, "僧侣");
	set("inquiry", ([
        "name": "贫僧就是本因",
        "龙树院" : "龙树院在雨花阁后面的松树林中",
	"枯荣" : "枯荣大师在龙树院参悟",
	"枯荣大师" : "枯荣大师在龙树院参悟",
	"松树林" : (: ask_kurong :),
        ]) );
        set("chat_chance_combat", 30);
        set("chat_msg_combat",({ 
              (: perform_action, "finger.sandie" :),
        }));            
        setup();
       
        carry_object("/d/tls/obj/changjian")->wield(); 
        carry_object("/d/tls/obj/nianzhu")->wear();
        carry_object("/d/tls/obj/jiasha")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}
string ask_kurong()
{
        object me,ob;
		 mapping ob_fam,my_fam;
		ob=this_player();
        me=this_object();
        ob_fam = (mapping)ob->query("family");
        my_fam = (mapping)me->query("family");  
       
      if ((ob_fam && ob_fam["family_name"] != "天龙寺")||ob->query("class") != "bonze") 
         return ("对不起，你不能去打扰枯荣大师！\n");
      if (ob_fam["generation"] == (my_fam["generation"] + 1)){
		  return ("松林很密，容易迷路，你一进林，向北走四步，向西走三步，再向北走一步，西走三步就到了 \n");
		   } else return ("你辈分不够，不能去拜见枯荣大师。 \n");

}
#include "ben.h";
