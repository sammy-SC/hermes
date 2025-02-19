/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import React from 'react';
import classnames from 'classnames';
import Layout from '@theme/Layout';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import withBaseUrl from '@docusaurus/withBaseUrl';
import styles from './styles.module.css';

const features = [
  {
    title: <>Faster App Launch</>,
    //imageUrl: 'img/undraw_docusaurus_mountain.svg',
    description: (
      <>
        Hermes-powered apps launch faster, thanks to build-time precompilation of JavaScript into efficient bytecode.
      </>
    ),
  },
  {
    title: <>Optimized for Mobile</>,
    //imageUrl: 'img/undraw_docusaurus_tree.svg',
    description: (
      <>
        Hermes is small in APK size, lean on memory, and starts instantly. It won't weigh your app down.
      </>
    ),
  },
  {
    title: <>Easy Integration</>,
    //imageUrl: 'img/undraw_docusaurus_react.svg',
    description: (
      <>
        It's simple to get started with Hermes in React Native apps. Hermes is open source and implements JavaScript standards.
      </>
    ),
  },
];

function Home() {
  const context = useDocusaurusContext();
  const {siteConfig = {}} = context;
  return (
    <Layout
      title="Hermes"
      description="JavaScript engine optimized for React Native">
      <header className={classnames('hero hero--primary', styles.heroBanner)}>
        <div className="container">
          <h1 className="hero__title">{siteConfig.title}</h1>
          <p className="hero__subtitle">{siteConfig.tagline}</p>
          <div className={styles.buttons}>
            <Link
              className={classnames(
                'button button--outline button--secondary button--lg',
                styles.getStarted,
              )}
              to={'https://facebook.github.io/react-native/docs/hermes'}>
              Start Using Hermes
            </Link>
          </div>
        </div>
      </header>
      <main>
        {features && features.length && (
          <section className={styles.features}>
            <div className="container">
              <div className="row">
                {features.map(({imageUrl, title, description}, idx) => (
                  <div
                    key={idx}
                    className={classnames('col col--4', styles.feature)}>
                    {imageUrl && (
                      <div className="text--center">
                        <img
                          className={styles.featureImage}
                          src={withBaseUrl(imageUrl)}
                          alt={title}
                        />
                      </div>
                    )}
                    <h3>{title}</h3>
                    <p>{description}</p>
                  </div>
                ))}
              </div>
            </div>
          </section>
        )}
      </main>
    </Layout>
  );
}

export default Home;
