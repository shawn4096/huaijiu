// king.c 段正明
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string enter();
string qinwang(object ob);
void create()
{
        set_name("段正明", ({ "duan zhengming", "duan", "master" }) );
        set("nickname", HIW"保定帝"NOR);
        set("title","大理皇帝");
        set("gender", "男性" );
        set("age", 48);
        set("str", 28);
        set("con", 28);
        set("dex", 28);
        set("int", 28);
        set("per", 26);
        set("max_qi", 4000);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("neili", 4000);
        set("qi", 4000);
        set("jingli", 3000);
        set("max_neili", 4000);
        set("jiali", 80);

        set("rank_info/respect", "殿下");
        create_family("天龙寺", 13, "俗家弟子");
        set("long", 
        "他看上去平易近人又颇有风度，气宇轩昂，眉目之间透着一股逼人的英气。\n");
        set("combat_exp", 1600000);
        set("score", 200000);              

        set_skill("parry", 200);
        set_skill("dodge", 180);
        set_skill("buddhism",180);
        set_skill("force", 200);
        set_skill("literate", 150);
        set_skill("sword", 180);
        set_skill("duanjia-jianfa", 180);
        set_skill("cuff", 200);
        set_skill("duanjia-quan", 200);
        set_skill("yiyang-zhi", 200);
        set_skill("finger", 200);
        set_skill("qiantian-yiyang", 200);
        set_skill("tianlong-xiang", 200);
		

        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "duanjia-jianfa");
        map_skill("sword", "duanjia-jianfa");
        map_skill("force", "qiantian-yiyang");
        map_skill("cuff", "duanjia-quan");
	map_skill("finger","yiyang-zhi");
        prepare_skill("finger","yiyang-zhi");
        set("inquiry", ([
        "入后宫" : (: enter :), 
        "亲王" : (: qinwang :),
        "name": "朕就是保定帝段正明。",
        "here": "这里便是大理皇宫。",        
        ]) );

        setup();
        carry_object("/d/dali/npc/obj/huangpao")->wear();
        carry_object("/clone/weapon/gangjian")->wield();
}

void init()
{
        object ob,me;
   //     mapping my_fam;
  //      int i;
        me=this_object();
        ob = this_player();
 //       i = ob->query_skill("liumai-shenjian",1);
 //       if (ob->query("family"))
 //       my_fam=ob->query("family"); 
        ::init();
        if (interactive(ob = this_player()) && living(this_object()) &&
                (int)ob->query_temp("killqueen")) {
                command ("say 你竟敢杀我的皇后，纳命来！\n");
                me->set_leader(ob);
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, ob);
        }
/*                     
       if ((my_fam["family_name"] == "大理")){
          ob->set("family/family_name","天龙寺");
          if (my_fam["generation"]<4) 
          {
          ob->set("family/generation", 14);
          ob->set_skill("buddhism",140);
        } else ob->set("family/generation", 15);
         if (ob->query_skill("liumai-shenjian",1)) {
	  ob->set_skill("yiyang-zhi",i);
	  ob->delete_skill("liumai-shenjian");
	  ob->set_skill("kurong-changong",100);
	  command ("say 你如果能接枯荣十招,可重新学习六脉 \n");
	        }
	      	
		command ("say 哈哈,今后大理天龙合并,你就是天龙寺俗家弟子了! \n");
          }
 */         
}

string enter()
{
        object ob;
        string target;
        ob = this_player();
        if ( ob->query("combat_exp") < 100000)
           return "你想进后宫干吗？";
        if ( ob->query_temp("fan")){
           string book;
           book=ob->query_temp("book_target");
           return("让你去找"+book+CYN"，还不快去。"NOR);
           }
        switch  (random(7)){
        case 0: target = HIW"天神篇"NOR; break;
        case 1: target = HIW"龙神篇"NOR; break;
        case 2: target = HIW"夜叉篇"NOR; break;
        case 3: target = HIW"乾达婆篇"NOR; break;
        case 4: target = HIW"阿修罗篇"NOR; break;
        case 5: target = HIW"迦楼罗篇"NOR; break;
        case 6: target = HIW"紧那罗篇"NOR; break;
        case 7: target = HIW"摩呼罗迦篇"NOR; break;
        }
        ob->set_temp("fan",1);
        ob->set_temp("book_target",target);
        return("想入后宫，先帮我把天龙八部的"+target+CYN"找来。"NOR);   
}

string qinwang(object ob)
{       
       string new_title,title,*title1,*title2;
       mapping fam;
       ob=this_player();
       fam = ob->query("family");       
       title1 =({ "承","平","定","乾","滇" });
       title2 =({ "东","南","西","北" });
       if ((!fam)||(fam["family_name"] != "天龙寺"))
          return RANK_D->query_respect(ob)+"与本国素无来往，不知此话从何谈起？";  
        if (ob->query("tls")&&ob->query("class")=="bonze")
                return RANK_D->query_respect(ob) + "已经贵为天龙寺高僧，这个亲王显然是不适合你的.";
       if (ob->query("dali_job") < 3000 && ob->query_skill("qiantian-yiyang",1) < 160)
          return RANK_D->query_respect(ob) + "为大理做的还不够，就想成为王爷了？";
       if (stringp(ob->query("qinwang")))
          return RANK_D->query_respect(ob) + "已经是我朝亲王了，怎么还来打听？";
       title= title1[random(sizeof(title1))]+title2[random(sizeof(title2))]+"王";
       new_title= "大理国"+title;
       ob->set("title",HIW + new_title + NOR);
       ob->set("qinwang", title);
       command("chat 哈哈哈，即日起朕封" + ob->query("name")+"为我"+new_title+"。");
       return "好吧，看你劳苦功高，朕就封你为"+ new_title +"。";       
       
}

void attempt_apprentice(object ob)
{     
        string name, new_name, *prename;
        prename = ({ "段", "段" });
        if (ob->query("tls")&&ob->query("class")=="bone") {
             command ("say 你已经是天龙寺出家弟子了，我不能再收你了！");
             return;
             } 
        if( (int)ob->query_skill("qiantian-yiyang",1) < 140 ){      
             command ("hmm");
             command ("say 你乾天一阳功如此之差，我可不收你！");
             return;
             }
        if(ob->query_int() < 33){
             command("say 武学之道必须悟性高，依我看" + RANK_D->query_respect(ob) + "的资质似乎不够？");
             return;
             }
        if(ob->query("shen") < 0){
             command("say 大理乃堂堂皇室，而这位" + RANK_D->query_respect(ob) + "眼露凶光，我看不适合在我大理呆下去了。");
             return;
             }
        command("smile");
        command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
        name = ob->query("name");
        new_name = prename[random(sizeof(prename))] + name[<4..<1];
        command("say 入我段家，从今以后你的名字就叫做" + new_name + "。");  
        ob->set("name", new_name);     
        command("recruit " + ob->query("id") );
        if (!ob->query("qinwang")) ob->set("title","大理国御前侍卫");
}

void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        ob->set("class", "officer");
}

int accept_object(object who, object ob)
{
        string bookname;
        bookname=ob->query("name");
        if ((bookname!=HIW"天神篇"NOR)
          &&(bookname!=HIW"龙神篇"NOR)
          &&(bookname!=HIW"夜叉篇"NOR)
          &&(bookname!=HIW"乾达婆篇"NOR)
          &&(bookname!=HIW"阿修罗篇"NOR)
          &&(bookname!=HIW"迦楼罗篇"NOR)
          &&(bookname!=HIW"紧那罗篇"NOR)
          &&(bookname!=HIW"摩呼罗迦篇"NOR))
            return notify_fail("段正明对你摇头道：我要这东西没用啊。\n");
       if ( bookname==this_player()->query_temp("book_target")){
          if ( ob->query_temp("find") == who->query("id")){ 
              command("smile");
              command("say 很好，你可以进后宫了。");
              who->set_temp("enter",1);
              who->delete_temp("book");
              call_out("destroying", 1, ob);
              return 1;
              }
              command("hmm");
              command("say 这好象不是你找到的吧。");
              call_out("destroying", 1, ob);
              return 1;
              }
       else{
              command("hmm");
              command("say 这不是我要的书，你再去找。");    
              call_out("destroying", 1, ob);
              return 1;
              }        
}

void destroying(object ob)
{
        destruct(ob);
        return;
}
