//mayi1.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
void create()
{
        object ob;
       set_name("张浩天", ({"zhang haotian","zhang","haotian"}));
       set("title","麻衣长老"); 
       set("nickname",HIY"铁掌四鹰"NOR);
       set("long",
    "他是一个年约六旬的老者，满头花发，两鬓斑白。\n"
    "他两侧的太阳穴高高鼓起，微闭的双目中时而闪过凌厉的眼神，似乎身怀绝技。\n"
       );

       set("gender", "男性");
       set("attitude", "peaceful");
       set("unique", 1);
       set("age", 60);
       set("shen_type", -10);
       set("str", 28);
       set("int", 23);
       set("con", 23);
       set("dex", 28);
       set("per", 20);
       set("max_qi", 1800);
       set("max_jing", 1000);
       set("neili", 2000);
       set("max_neili", 2000);
       set("jiali", 50);
       set("combat_exp", 600000);
       set("score", 10000);

       set_skill("force", 120);
       set_skill("guiyuan-tunafa", 120);
       set_skill("dodge", 120);
       set_skill("literate", 100);
       set_skill("shuishangpiao", 120);
       set_skill("strike", 120);
       set_skill("tiezhang-zhangfa", 120);
       set_skill("parry", 120);
       set_skill("blade", 150);
       set_skill("liuye-daofa", 150);
       set_skill("tiezhang-xinfa",150);

       map_skill("force", "guiyuan-tunafa");
       map_skill("dodge", "shuishangpiao");
       map_skill("strike", "tiezhang-zhangfa");
       map_skill("parry", "tiezhang-zhangfa");
       map_skill("blade", "liuye-daofa");
       prepare_skill("strike", "tiezhang-zhangfa");

       create_family("铁掌帮", 15, "长老");
       set("inquiry", ([
//           "斧法概要" : (: ask_book :),
           ]));
       
       setup();
        if (clonep()) {
       ob = unew("/d/tiezhang/obj/yuanyang-yue");
       if (ob) {
                destruct(ob);
                ob = unew("/d/tiezhang/obj/zimu-huan");
                }
       if (!ob) ob = unew("/d/tiezhang/obj/gangfu");
                ob->move(this_object());
                ob->wield();
                carry_object("/d/tiezhang/npc/obj/mayi")->wear();
        }

}

void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }       
     
}
/*
void greeting(object me)
{
        mapping myfam;
        int shen;
        myfam = (mapping)me->query("family");
        shen = me->query("shen");

        if(shen >= 0 &&(myfam["family_name"] == "铁掌帮" && myfam["master_name"] != "上官剑南")){
        command("say 老子最看不惯你这种自命大侠的人，从今天起你被逐出铁掌帮了！");
        command("expell " + me->query("id"));
        }
}
*/
void attempt_apprentice(object ob)
{
      object me  = this_object();
      mapping fam = ob->query("family");

        if(!fam || fam["family_name"] != "铁掌帮"){
                command("say "+RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
                }
         if (fam && fam["family_name"] != "铁掌帮" 
            && (int)ob->query("is/tiezhang") == 1 ) {
                message_vision(BLU "$N！你这个被逐出本帮的叛徒还回来干什么 ？？？\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
                }
        if ((int)ob->query("shen") >= -5000) {
                command("hehe");
                command("say 铁掌帮可不收心慈手软的人做弟子。\n");
                return;
                }
        if(fam["master_name"] == "裘千仞"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"已是帮主亲传弟子，"+RANK_D->query_self(me)+"怎敢再收你为徒？"); 
                return;
                }
        if(fam["master_name"] == "上官剑南"){
                command("ah");
                command("say 上官帮主不是早已故世多年了嘛？");
                command("say "+RANK_D->query_respect(ob)+"原来是老帮主关门弟子啊，失敬。"+RANK_D->query_self(me)+"怎敢再收你为徒？"); 
                return;
                }   
        if ((int)ob->query_skill("guiyuan-tunafa", 1) <= 30) {
                command("say 要学更为高深的武功，必须有高深的内功修为。"); 
                command("say " + RANK_D->query_respect(ob)+"是否还应该在归元吐纳法上多下点功夫？");
                return;
                }
/*
        if ((int)ob->query_str() < 20) {
                command("say 要学裂天斧法，必须要有一定的臂力。\n"); 
                command("say " + RANK_D->query_respect(ob)+"是否臂力还有所欠缺？");
                return;
                }            
*/
                command("say 好吧，我就收下你了。希望你苦练铁掌帮神功，将之发扬光大。\n");
                command("recruit " + ob->query("id"));
                ob->set("is/tiezhang",1);
                ob->set("class","brigand");


}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                add("apprentice_available", -1);
}

/*
string ask_book()
{
        mapping fam; 
        object ob;

        if (!(fam = this_player()->query("family")) 
            || fam["family_name"] != "铁掌帮")
                return RANK_D->query_respect(this_player()) + 
                "与本派素无来往，不知此话从何谈起？"; 
         ob = unew("/d/tiezhang/obj/axe_book");
        if(!clonep(ob)) return "你来晚了，「斧法概要」已经被你师兄拿去了。";
        if(clonep(ob) && ob->violate_unique()){
           destruct(ob);
           return "你来晚了，「斧法概要」已经被你师兄拿去了。";
           } 
        ob->move(this_player());
        return "好吧，这本「斧法概要」你拿回去好好钻研。";
}
*/
