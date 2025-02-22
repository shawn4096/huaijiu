// lugy.c
// By jpei
// 收徒。 Modified by Numa 19990917
// Modified by Darken for taohua quest

inherit NPC;
inherit F_MASTER;
#include "nadir.c"

// string ask_yao1();
string ask_yao2();
int ask_quest();

object ob = this_object();
void create()
{
        set_name("陆冠英", ({"lu guanying", "lu", "guanying"}) );
        set("title","归云庄少庄主");
        set("long", "他身穿熟罗长袍，背厚膀宽，躯体壮健。\n");
        set("gender", "男性" );
        set("age", 27);
        set("attitude", "peaceful");
        set("apprentice",1);
        set("str",25);
        set("int",25);
        set("con",27);
        set("dex",26);
        set("max_qi", 1200);
        set("max_jing", 1000);
        set("eff_jingli", 1200);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 30);
        set("combat_exp", 300000);

        set_skill("force", 100);
        set_skill("bihai-chaosheng", 90);
        set_skill("dodge", 90);
        set_skill("suibo-zhuliu", 90);
        set_skill("qimen-baguazhen",100);
        set_skill("parry", 90);
        set_skill("strike", 100);
        set_skill("luoying-zhang", 90);
        set_skill("leg", 110);
        set_skill("xuanfeng-tui", 110);
        set_skill("sword", 90);
        set_skill("yuxiao-jian", 80);
        set_skill("taoism", 90);
        set_skill("literate", 100);
        set_skill("qimen-bagua", 60);

        map_skill("force", "bihai-chaosheng");
        map_skill("dodge", "suibo-zhuliu");
        map_skill("strike", "luoying-zhang");
        map_skill("leg", "xuanfeng-tui");
        map_skill("parry", "luoying-zhang");
        map_skill("sword", "yuxiao-jian");
        prepare_skill("strike", "luoying-zhang");

        set("rank_info/respect", "少庄主");
        set("shen_type", 1);
        set("shen", 200);
//      set("vendetta_mark", "桃花岛");
        create_family("桃花岛", 3, "弟子");
        set("class", "fighter");
//        set("yao", 10);   
        set("unique", 1);   

        set("inquiry", ([
                "name": "在下陆冠英，是这里的少庄主。",
                "rumors": (: ask_quest :),
                "here": "这里是归云庄，你随便转转吧，累了请到客房休息。",
                "东邪": "那是我祖师爷呀，，蒙他老人家恩准，我才能跟父亲学艺。",
                "黄药师": "那是我祖师爷呀，，蒙他老人家恩准，我才能跟父亲学艺。",
                "寒雨": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
                "jpei": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
                "桃花岛": "听说是师祖住的地方，可惜没有去看过。",
                "陆乘风": "是我的父亲，找他老人家有什么事吗？",
                "陆冠英": "不敢，就是在下。",
                "归云庄": "这里是花了我父亲无数心血才建起来的，与别的庄院相比如何？",
                "太湖": "就在庄前不远，是一个烟波浩淼的大湖。",
                "药" : "爹爹让我保管灵药，桃花岛弟子可以到我这里领取。",
//              "三才聚精丹": (: ask_yao1 :),
//                "六壬集气丸": (: ask_yao2 :),
                  "六壬集气丸": "我交给我夫人保管了。",
                "九花玉露丸":   "九花玉露丸炼制奇难无比，我这里可没有! ",
        ]) );

        setup();

        carry_object(__THD__"obj/wht-cloth.c")->wear();
}

// 此处加入收徒
void attempt_apprentice(object ob)
{
	object me= this_object();
	mapping fam= ob->query("family");
	if( fam && ob->query("combat_exp", 1) > 10000){
		command("say 你已经是"+ob->query("family/family_name")+"的高手了，我桃花岛可不敢收你。");
		return;
	}
        if ( fam && fam["family_name"] =="桃花岛" && (int)ob->query("family/generation")==3){
                command("say "+RANK_D->query_respect(ob)+"已经是家父的弟子，"+RANK_D->query_self(me)+"怎敢再收你为徒？"); 
                return;
        }
        if (fam && fam["family_name"] == "桃花岛" && (int)ob->query("family/generation")==2){
                command("say "+RANK_D->query_respect(ob)+"已经是祖师爷的弟子，"+RANK_D->query_self(me)+"怎敢再收你为徒？"); 
                return;
        }

        if (ob->query("shen") <= -200000) {
                command("say 祖师爷生平最讨厌两种人，你们这种无恶不作的邪魔外道就是其一！");
                return;
        }
        if (ob->query("shen") >= 200000) {
                command("say 祖师爷生平最讨厌两种人，你们这种自命大侠的沽名钓誉之徒就是其一！");
                return;
        }
// change app int from 28 -> 24
        if (ob->query_int() < 24) {
                command("say 你的才气太差，不适合学我桃花岛的武技！");
                return;
        }     
        command("look " + ob->query("id"));
        command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("recruit " + ob->query("id"));
        ob->set("class", "fighter");
}
        
void init()
{
        object ob = this_player();

        ::init();
        if (ob->query("family/family_name") == "桃花岛" && (int)ob->query("family/generation")>2)
        {
                if ((int)ob->query("shen") <= -200000)
                {
                        message_vision("陆冠英对$N喝道：你做恶多端，有辱祖师爷清名，还敢来见我？！\n", ob);
                        message_vision("陆冠英对$N喝道：从今天起，你再也不是桃花岛的弟子了！\n", ob);
                        command("expell "+ ob->query("id"));
                        ob->set("title", "桃花岛弃徒");
                }
                else if ((int)ob->query("shen") >= 200000)
                {
                        message_vision("陆冠英对$N喝道：你是大侠，我早就说过，祖师爷最恨沽名吊誉的伪君子。\n", ob);
                        message_vision("陆冠英对$N喝道：从今天起，你再也不是桃花岛的弟子了！\n", ob);
                        command("expell "+ ob->query("id"));
                        ob->set("title", "桃花岛弃徒");
                }
        }
}

int ask_quest()
{
        object ob = this_player(); 
        mapping fam;
       
     if (!(fam = ob->query("family")) || fam["family_name"] != "桃花岛")
        return notify_fail(RANK_D->query_respect(ob) + "能为我们抵御蒙古兵么？\n");

     if (ob->query_temp("thd/onquest")!=4)
        return notify_fail(RANK_D->query_respect(ob) + "能为我们抵御蒙古兵么？\n");

        command("consider");
        command("say 今天早上有人送了个骷髅头来，上面竟然有五个指孔。");
        command("say 爹爹一看到便要我送家人避难去，不知道为什么。");
        command("kick");
        ob->set_temp("thd/onquest",5);
        return 1;
}

