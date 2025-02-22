// Npc: /kungfu/class/shaolin/xuan-sheng.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;


void create()
{
        object ob;
        set_name("玄生大师", ({
                "xuansheng dashi",
                "xuansheng",
                "dashi",
        }));
        set("long",
                "他是一位白须白眉的老僧，身穿一袭银丝棕黄袈裟。他身材瘦高，\n"
                "太阳穴微微突起，坐在铺垫上参禅。\n"
        );


        set("nickname", "证道院首座");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 150);
        set("combat_exp", 1000000);
        set("score", 500000);

        set_skill("force", 140);
        set_skill("yijin-jing", 140);
        set_skill("dodge", 140);
        set_skill("shaolin-shenfa", 140);
        set_skill("parry", 140);        
        set_skill("strike", 140);
        set_skill("cuff", 140);
        set_skill("leg", 140);
        set_skill("finger", 140);
        set_skill("staff", 140);
        set_skill("strike", 140);
        set_skill("jingang-quan", 140);
        set_skill("wuchang-zhang", 140);
        set_skill("ruying-suixingtui", 140);    
        set_skill("mohe-zhi", 140);
        set_skill("banruo-zhang", 140);
        set_skill("buddhism", 140);
        set_skill("literate", 140);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("finger", "mohe-zhi");
        map_skill("strike", "banruo-zhang");
        map_skill("leg", "ruying-suixingtui");
        map_skill("staff", "wuchang-zhang");
        map_skill("parry", "wuchang-zhang");

        prepare_skill("finger", "mohe-zhi");
        prepare_skill("leg", "ruying-suixingtui");
        
        create_family("少林派", 36, "弟子");

        

        setup();

        if (clonep()) {
                ob = unew(BINGQI_D("jiuhuan-zhang"));                
                if (!ob) ob = unew(BINGQI_D("chanzhang"));
                ob->move(this_object());
                ob->wield();
                carry_object("/d/shaolin/obj/xuan-cloth")->wear();
        }
       
}


void attempt_apprentice(object ob)
{
        object me; 
        mapping ob_fam, my_fam;
        string name;

        me = this_object();
        my_fam  = me->query("family");

        name = ob->query("name");

        if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "少林派")
        {
                command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
        }

        if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派") 
        {
                command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺内学艺。");
                return;
        }

        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
                return;
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..1] == "澄")
        {
                command("say " + ob_fam["master_name"] + "的徒弟怎麽跑到我这儿来了，哈哈哈 !");
                command("recruit " + ob->query("id"));
        }
        else
        {
                command("say " + RANK_D->query_respect(ob) + "，你辈份不合，不能越级拜师。");
                return;
        }

        return;
}


