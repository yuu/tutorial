<?php

namespace AppBundle\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;

class BlogController extends Controller
{
    private function createBlogList($date, $title)
    {
        return Array('targetDate' => $date, 'title' => $title);
    }

    public function latestListAction()
    {
        $em = $this->getDoctrine()->getManager();
        $blogArticleRepository = $em->getRepository('AppBundle:BlogArticle');
        $blogList = $blogArticleRepository->findBy([], ['targetDate' => 'DESC']);

        return $this->render('Blog/latestList.html.twig', array('blogList' => $blogList));
    }
}