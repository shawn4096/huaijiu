
inherit NPC;

 
void consider();

void create()
{
       set_name("卫天望", ({ "wei tianwang","wei" }) );
       set("gender", "男性" );
       set("age", 58);
       set("long", " \n");
       set("attitude", "peaceful");
        set("nickname", "西域少林长老");
//      set("class", "bonze");
       set("str", 20);
       set("con", 35);
       set("int", 25);
       set("dex", 35);
 

       set("max_qi", 3000);
       set("max_jing", 1500);
       set("neili", 300);
       set("max_neili", 3000);
       set("jiali", 100);
       set("shen_type", 1);
//       set("startroom","/d/wudang/xiaolu2");

        
       set("combat_exp", 800000);

       set_skill("force", 120); 
       set_skill("cuff", 120);
       set_skill("sword", 120);
       set_skill("dodge", 140);
       set_skill("parry", 140);
       set_skill("shaolin-shenfa", 140);
       set_skill("literate", 100);
       set_skill("jingang-quan", 120); 
       set_skill("yijin-jing", 150);
       set_skill("buddhism", 150);
         set("unique", 1);
                map_skill("force", "hunyuan-yiqi");
       map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("parry", "jingang-quan");
        prepare_skill("cuff", "jingang-quan");

       create_family("西域少林", 19, "弟子");

       set("chat_chance", 20);
/*       set("chat_msg", ({
               "西域少林虽是少林分支，但外功的刚猛却有独到之处。\n",
               "出家人虽戒杀生，但锄恶降魔却也是我佛本意。\n",
                 (: random_move :)
       }) );*/

       setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void kill_ob(object me)
{
        set("chat_chance_combat", 50);
       set("chat_msg_combat", ({
               (: perform_action, "cuff.fumo" :)
        }));
        ::kill_ob(me);       
} 
