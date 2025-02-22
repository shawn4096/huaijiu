//wanzhenshan.c 

inherit NPC;

int ask_liguan(); 
void create()
{
        set_name("万震山", ({ "wan zhenshan","wan","zhenshan", "guanzhu" }));
        set("title", "襄阳武馆馆主");
        set("nickname", "五云手");
        set("gender", "男性");
        set("age", 62);
        set("str", 30);
        set("dex", 26);
        set("long", "这人紫金脸庞，面带威严，威武有力，站在那里就象是一座铁塔。\n");
        set("combat_exp", 100000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set("unique", 1);
         
        set_skill("force", 90);
        set_skill("strike", 90);  
        set_skill("dodge", 90);
        set_skill("parry", 90);     
        set_skill("shenzhao-jing", 90);
        map_skill("force","shenzhao-jing");

        set("inquiry", 
                ([
                        "工作" : "呵呵，你去找我的大徒弟吧，他会安排你的!",
                        "练功" : "东西练武场都可以练的，你去那儿练吧!",
                        "离馆" : (:ask_liguan:),                        
                ]));

        setup();
        carry_object(ARMOR_D("jinduan"))->wear();
}

int ask_liguan()
{
          object ob;
          ob = this_player();
          if(! ob->query("enter_wuguan")){
            command("say 你不是已经来打听过了么？");
            return 1;
          }
          if(ob ->query("combat_exp") > 3000){          
            command("nod "+ob->query("id"));
            command("say 这位" + RANK_D->query_respect(ob)+"可以出去闯荡江湖了，江湖险恶，可千万小心啊。去和我\n"+
                    "四徒弟孙均去说一声吧，他会安排的。");
            ob->delete("enter_wuguan");
            return 1;
          }
          else{
            command("pat "+ob->query("id"));
            command("say 这位" + RANK_D->query_respect(ob)+"的经验还太差，江湖太危险，你还是乖乖在武馆练功吧。");
            return 1;
          }
}
