#include <ansi.h>
inherit NPC;

void create()
{
        set_name("ほのか", ({"honoka"}));
        set("long", 
                "慢海�嬰�主��寄寄議凛商��綜繁匯需阻祥浪散。\n"
                "慢挫�餾槝音怯鰻州�耽肝匯心欺僣祥挫互佶。\n");
        set("title",HIG"溺舞劔"NOR);
        set("nickname",HIY"欠にのせたラウ、ソング"NOR);
        set("rank_info/rude", "ほのか");
        set("attitude","peaceful");
        set("str", 40);
        set("dex", 40);
        set("con", 40);
        set("int", 40);
        set("per", 100);
        set("gender", "溺來");
        set("age", 17);
        set("shen_type", 0);
        
        set("combat_exp", 2750000);
        set("max_qi", 7000);
        set("max_jing", 7000);
        set("eff_jingli",7000);
        set("max_jingli",7000);
        set("eff_jing",7000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali",70);
        
        set_skill("force", 300);
        set_skill("jiuyin-zhengong", 300);
        set_skill("dodge", 300);
        set_skill("jiuyin-shenfa", 300);
        set_skill("parry", 300);
        set_skill("strike", 300);
        set_skill("jiuyin-shenzhang", 300);
        set_skill("sword", 300);
        set_skill("xuanyin-jian",300);
        set_skill("literate",999);
        set_skill("qimen-bagua", 999);
        set_skill("taoism", 999);
        set_skill("cuff", 300);
        set_skill("dafumo-quan", 300);
        set_skill("claw", 300);
        set_skill("jiuyin-shenzhua", 300);
        set_skill("whip", 300);
        set_skill("yinlong-bian", 300);

        map_skill("force", "jiuyin-zhengong");
        map_skill("dodge", "jiuyin-shenfa");
        map_skill("strike", "jiuyin-shenzhang");
        map_skill("cuff", "dafumo-quan");
        map_skill("claw", "jiuyin-shenzhua");
        map_skill("parry", "xuanyin-jian");
        map_skill("sword", "xuanyin-jian");
        map_skill("whip", "yinlong-bian");

        prepare_skill("strike", "jiuyin-shenzhang");
        prepare_skill("cuff", "dafumo-quan");

        set("inquiry", ([
                "name": "煉煉��厘頁遭昧欠議溺涛嗔ほのか",
                "darken": "麿頁厘槻涛嗔��麿繁恷挫阻。",
                "遭昧欠": "麿頁厘槻涛嗔��麿繁恷挫阻。",
        ]));
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "zongjue" :),
                (: perform_action, "dodge.huanyinbu" :),
                (: perform_action, "sword.xuanyin" :),
                (: perform_action, "strike.yinyang" :),
        }));

        setup();
        
//        carry_object(__DIR__"obj/white_cloth")->wear();
  //      carry_object(__DIR__"obj/dongxiao")->wield();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) 
       {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if ((string)ob->query("id")=="darken")
        {
              command("kiss " +ob->query("id"));
              command("blush");
              return;
        } else {
              command("hi " + ob->query("id"));
              command("say " + ob->query("name") + "頁栖孀昧欠悟悟議担��");
              command("smile");
              return;
        }
}


void relay_emote(object me,string arg)
{
        if ((string)me->query("id")=="darken")
        {
                switch (arg)
                {
                case "love":
                case "kiss":
                case "kiss2":
                case "lovelook":
                        command("lovelook " + me->query("id"));
                        break;
                case "smash":
                case "kick":
                case "slap":
                case "slapsb":
                case "hammer":
                case "claw":
                case "admit":
                case "crazy":
                        command("angry " + me->query("id"));
                        break;
                default:
                        command("xixi");
                        command(arg + " " + me->query("id"));
                        break;
                }
                return;
        }
        else {
                command("kick "+me->query("id"));
                command("shameless "+me->query("id"));
                return;
             }
}

